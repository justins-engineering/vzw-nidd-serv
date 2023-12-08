/** @headerfile request_handler.h */
#include "request_handler.h"

#define JSMN_HEADER

#include <config.h>
#include <jsmn.h>
#include <nxt_clang.h>
#include <nxt_unit.h>
#include <stdio.h>
#include <time.h>

#include "../config/vzw_secrets.h"
#include "http_get_stop.h"
#include "json_helpers.h"
#include "parse_stop_json.h"
#include "vzw_connect.h"

#define CONTENT_TYPE "Content-Type"
#define TEXT_PLAIN "text/plain; charset=utf-8"
#define JSON_UTF8 "application/json; charset=utf-8"

static unsigned int minutes_to_departure(Departure *departure) {
  long edt_ms = departure->etd;
  struct timespec ts;
  timespec_get(&ts, TIME_UTC);

  long time_ms = (long)(ts.tv_sec * 1000) + (long)(ts.tv_nsec / 1000000);
  return (unsigned int)(edt_ms - time_ms) / 60000;
}

static int get_vzw_tokens(char *vzw_auth_token, char *vzw_m2m_token) {
  int rc;

  rc = get_vzw_auth_token(VZW_PUBLIC_KEY ":" VZW_PRIVATE_KEY, vzw_auth_token);
  if (nxt_slow_path(rc != NXT_UNIT_OK)) {
    goto fail;
  }
  PRINTDBG("auth token: %s", vzw_auth_token);

  rc = get_vzw_m2m_token(
      VZW_USERNAME, VZW_PASSWORD, vzw_auth_token, vzw_m2m_token
  );
  if (nxt_slow_path(rc != NXT_UNIT_OK)) {
    goto fail;
  }
  PRINTDBG("m2m token: %s", vzw_m2m_token);

fail:
  return rc;
}

void request_handler(nxt_unit_request_info_t *req) {
  int rc;
  char *p;
  // ssize_t res;
  nxt_unit_buf_t *buf;
  unsigned int min;
  char id_str[12];

  static Stop stop = {.last_updated = 0, .id = STOP_ID};
  size_t stop_size = sizeof(stop);

  char vzw_auth_token[50] = "\0";
  char vzw_m2m_token[50] = "\0";

  /** HTTP response body buffer with size defined by the STOP_JSON_BUF_SIZE
   * macro. */
  char json_buf[STOP_JSON_BUF_SIZE] = "\0";

  rc = nxt_unit_response_init(
      req, 200 /* Status code. */, 1 /* Number of response headers. */,
      nxt_length(CONTENT_TYPE) + nxt_length(JSON_UTF8)
  );
  if (nxt_slow_path(rc != NXT_UNIT_OK)) {
    nxt_unit_req_log(req, NXT_UNIT_LOG_ALERT, "nxt_unit_response_init failed");
    goto fail;
  }

  rc = nxt_unit_response_add_field(
      req, CONTENT_TYPE, nxt_length(CONTENT_TYPE), JSON_UTF8,
      nxt_length(JSON_UTF8)
  );
  if (nxt_slow_path(rc != NXT_UNIT_OK)) {
    nxt_unit_req_log(
        req, NXT_UNIT_LOG_ALERT, "nxt_unit_response_add_field failed"
    );
    goto fail;
  }

  rc = nxt_unit_response_send(req);
  if (nxt_slow_path(rc != NXT_UNIT_OK)) {
    nxt_unit_req_alert(req, "first nxt_unit_response_send failed");
    goto fail;
  }

  // rc = get_vzw_tokens(&vzw_auth_token[0], &vzw_m2m_token[0]);
  // if (nxt_slow_path(rc != NXT_UNIT_OK)) {
  //   nxt_unit_req_error(req, "Failed to get VZW credentials");
  //   goto fail;
  // }

  rc = http_request_stop_json(req, json_buf);
  if (nxt_slow_path(rc != NXT_UNIT_OK)) {
    nxt_unit_req_alert(req, "http_request_routes failed");
    goto fail;
  }

  rc = parse_stop_json(json_buf, &stop);

  stop_size += sizeof(RouteDirection) * stop.routes_size;

  for (int i = 0; i < stop.routes_size; i++) {
    struct RouteDirection route_direction = stop.route_directions[i];
    stop_size += sizeof(Departure) * route_direction.departures_size;
  }

  buf = nxt_unit_response_buf_alloc(
      req, ((req->request_buf->end - req->request_buf->start) + stop_size)
  );

  if (nxt_slow_path(buf == NULL)) {
    rc = NXT_UNIT_ERROR;
    goto fail;
  }

  p = buf->free;

  *p++ = '{';
  p = json_obj_id_str(p, stop.id, strlen(stop.id));
  *p++ = '[';

  for (int i = 0; i < stop.routes_size; i++) {
    struct RouteDirection route_direction = stop.route_directions[i];

    // p = json_obj_id_str(p, "routes", strlen("routes"));

    *p++ = '{';
    p = json_obj_id_str(p, "direction", strlen("direction"));
    p = json_obj_value_str(p, &route_direction.direction_code, 1);
    *p++ = ',';

    p = json_obj_id_str(p, "id", strlen("id"));
    sprintf(id_str, "%d", route_direction.id);
    p = json_obj_value_str(p, id_str, strlen(id_str));
    *p++ = ',';

    // p = json_obj_id_str(p, "departures", strlen("departures"));
    // *p++ = '[';

    for (int j = 0; j < route_direction.departures_size; j++) {
      struct Departure departure = route_direction.departures[j];

      min = minutes_to_departure(&departure);
      // *p++ = '{';
      // sprintf(id_str, "%d", min);
      p = json_obj_id_str(p, "mtd", strlen("mtd"));
      p = json_obj_value_num(p, min);
      *p++ = ',';

      p = json_obj_str(
          p, "text", strlen("text"), departure.display_text,
          strlen(departure.display_text)
      );

      // *p++ = '}';
      // if (j < (route_direction.departures_size - 1)) {
      //   *p++ = ',';
      // }
    }
    // *p++ = ']';
    *p++ = '}';
    if (i < (stop.routes_size - 1)) {
      *p++ = ',';
    }
  }
  *p++ = ']';
  *p++ = '}';

  buf->free = p;
  rc = nxt_unit_buf_send(buf);
  if (nxt_slow_path(rc != NXT_UNIT_OK)) {
    nxt_unit_req_error(req, "Failed to send buffer");
    goto fail;
  }

fail:
  nxt_unit_request_done(req, rc);
}
