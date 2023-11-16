
/*
 * Copyright (C) NGINX, Inc.
 */

#include <curl/curl.h>
#include <nxt_clang.h>
#include <nxt_unit.h>
#include <nxt_unit_request.h>
#include <pthread.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "http_get_stop.h"
#include "nidd_client.h"
#include "parse_stop_json.h"
#include "stop.h"

#define CONTENT_TYPE "Content-Type"
#define TEXT_PLAIN "text/plain; charset=utf-8"
#define JSON_UTF8 "application/json; charset=utf-8"

static int thread_count;
static pthread_t *threads;

static unsigned int minutes_to_departure(Departure *departure) {
  long edt_ms = departure->etd;
  struct timespec ts;
  timespec_get(&ts, TIME_UTC);

  long time_ms = (long)(ts.tv_sec * 1000) + (long)(ts.tv_nsec / 1000000);
  return (unsigned int)(edt_ms - time_ms) / 60000;
}

static inline char *copy(char *p, const void *src, uint32_t len) {
  memcpy(p, src, len);
  return p + len;
}

static void *worker(void *main_ctx) {
  int rc;
  nxt_unit_ctx_t *ctx;

  ctx = nxt_unit_ctx_alloc(main_ctx, NULL);
  if (ctx == NULL) {
    return NULL;
  }

  nxt_unit_debug(ctx, "start worker");

  rc = nxt_unit_run(ctx);

  nxt_unit_debug(ctx, "worker finished with %d code", rc);

  nxt_unit_done(ctx);

  return (void *)(intptr_t)rc;
}

static int ready_handler(nxt_unit_ctx_t *ctx) {
  int i, err;

  nxt_unit_debug(ctx, "ready");

  if (thread_count <= 1) {
    return NXT_UNIT_OK;
  }

  threads = nxt_unit_malloc(ctx, sizeof(pthread_t) * (thread_count - 1));
  if (threads == NULL) {
    return NXT_UNIT_ERROR;
  }

  for (i = 0; i < thread_count - 1; i++) {
    err = pthread_create(&threads[i], NULL, worker, ctx);
    if (err != 0) {
      return NXT_UNIT_ERROR;
    }
  }

  return NXT_UNIT_OK;
}

static void stop_request_handler(nxt_unit_request_info_t *req) {
  int rc;
  char *p;
  ssize_t res;
  nxt_unit_buf_t *buf;
  unsigned int min;
  char id_str[12];

  static Stop stop = {.last_updated = 0, .id = STOP_ID};
  size_t stop_size = sizeof(stop);

  /** HTTP response body buffer with size defined by the STOP_JSON_BUF_SIZE
   * macro. */
  char json_buf[STOP_JSON_BUF_SIZE] = "\0";

  char vzw_auth_token[37] = "\0";
  char vzw_m2m_token[49] = "\0";

  rc = nxt_unit_response_init(
      req, 200 /* Status code. */, 1 /* Number of response headers. */,
      nxt_length(CONTENT_TYPE) + nxt_length(TEXT_PLAIN)
  );
  if (nxt_slow_path(rc != NXT_UNIT_OK)) {
    nxt_unit_req_log(req, NXT_UNIT_LOG_ALERT, "nxt_unit_response_init failed");
    goto fail;
  }

  rc = nxt_unit_response_add_field(
      req, CONTENT_TYPE, nxt_length(CONTENT_TYPE), TEXT_PLAIN,
      nxt_length(TEXT_PLAIN)
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

  p = copy(p, "Stop ID: ", strlen("Stop ID: "));
  p = copy(p, stop.id, strlen(stop.id));
  *p++ = '\n';

  for (int i = 0; i < stop.routes_size; i++) {
    struct RouteDirection route_direction = stop.route_directions[i];
    nxt_unit_req_log(
        req, NXT_UNIT_LOG_INFO,
        "========= Route ID: %d; Direction: %c; Departures size: %d "
        "========= ",
        route_direction.id, route_direction.direction_code,
        route_direction.departures_size
    );

    *p++ = '\n';

    sprintf(id_str, "%d", route_direction.id);
    p = copy(p, "Route ID: ", strlen("Route ID: "));
    p = copy(p, id_str, strlen(id_str));
    *p++ = '\n';

    p = copy(p, "Route Direction: ", strlen("Route Direction: "));
    *p++ = route_direction.direction_code;
    *p++ = '\n';

    sprintf(id_str, "%d", route_direction.departures_size);
    p = copy(p, "Departures size: ", strlen("Departures size: "));
    p = copy(p, id_str, strlen(id_str));
    *p++ = '\n';

    for (int j = 0; j < route_direction.departures_size; j++) {
      struct Departure departure = route_direction.departures[j];

      min = minutes_to_departure(&departure);
      nxt_unit_req_log(
          req, NXT_UNIT_LOG_INFO, "Display text: %s", departure.display_text
      );
      nxt_unit_req_log(req, NXT_UNIT_LOG_INFO, "Minutes to departure: %d", min);

      p = copy(p, "Display text: ", strlen("Display text: "));
      p = copy(p, departure.display_text, strlen(departure.display_text));
      *p++ = '\n';

      sprintf(id_str, "%d", min);
      p = copy(p, "Minutes to departure: ", strlen("Minutes to departure: "));
      p = copy(p, id_str, strlen(id_str));
      *p++ = '\n';
    }
  }

  buf->free = p;

  rc = nxt_unit_buf_send(buf);

  get_vzw_m2m_token(req, "username", "password", "authtoken", "m2mtoken");

fail:
  nxt_unit_request_done(req, rc);
}

int main(int argc, char **argv) {
  int i, err;
  nxt_unit_ctx_t *ctx;
  nxt_unit_init_t init;

  curl_global_init(CURL_GLOBAL_NOTHING);

  if (argc == 3 && strcmp(argv[1], "-t") == 0) {
    thread_count = atoi(argv[2]);
  }

  memset(&init, 0, sizeof(nxt_unit_init_t));

  init.callbacks.request_handler = stop_request_handler;
  init.callbacks.ready_handler = ready_handler;

  ctx = nxt_unit_init(&init);
  if (ctx == NULL) {
    return 1;
  }

  err = nxt_unit_run(ctx);

  nxt_unit_debug(ctx, "main worker finished with %d code", err);

  if (thread_count > 1) {
    for (i = 0; i < thread_count - 1; i++) {
      err = pthread_join(threads[i], NULL);

      if (nxt_fast_path(err == 0)) {
        nxt_unit_debug(ctx, "join thread #%d", i);

      } else {
        nxt_unit_alert(
            ctx, "pthread_join(#%d) failed: %s (%d)", i, strerror(err), err
        );
      }
    }
    nxt_unit_free(ctx, threads);
  }

  nxt_unit_done(ctx);
  curl_global_cleanup();

  nxt_unit_debug(NULL, "main worker done");

  return 0;
}
