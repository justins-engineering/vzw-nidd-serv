/** @headerfile request_handler.h */
#include "request_handler.h"

#include <nxt_unit_request.h>
#include <nxt_unit_typedefs.h>

#define JSMN_HEADER

#include <config.h>
#include <jsmn.h>
#include <nxt_clang.h>
#include <nxt_unit.h>
#include <nxt_unit_sptr.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "../config/vzw_secrets.h"
#include "json_helpers.h"
#include "vzw_connect.h"

#define CONTENT_TYPE "Content-Type"
#define TEXT_HTML_UTF8 "text/html; charset=utf-8"
#define TEXT_PLAIN_UTF8 "text/plain; charset=utf-8"
#define JSON_UTF8 "application/json; charset=utf-8"

static inline char *copy(char *p, const void *src, uint32_t len) {
  memcpy(p, src, len);
  return p + len;
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

static int response_init(
    nxt_unit_request_info_t *req_info, int rc, uint16_t status, char *type
) {
  rc = nxt_unit_response_init(
      req_info, status, 1, nxt_length(CONTENT_TYPE) + strlen(type)
  );
  if (nxt_slow_path(rc != NXT_UNIT_OK)) {
    nxt_unit_req_log(
        req_info, NXT_UNIT_LOG_ALERT, "nxt_unit_response_init failed"
    );
    return 1;
  }

  rc = nxt_unit_response_add_field(
      req_info, CONTENT_TYPE, nxt_length(CONTENT_TYPE), type, strlen(type)
  );
  if (nxt_slow_path(rc != NXT_UNIT_OK)) {
    nxt_unit_req_log(
        req_info, NXT_UNIT_LOG_ALERT, "nxt_unit_response_add_field failed"
    );
    return 1;
  }

  rc = nxt_unit_response_send(req_info);
  if (nxt_slow_path(rc != NXT_UNIT_OK)) {
    nxt_unit_req_alert(req_info, "first nxt_unit_response_send failed");
    return 1;
  }

  return 0;
}

void vzw_request_handler(
    nxt_unit_request_info_t *req_info, void *path, int rc
) {
  char *p;
  // ssize_t res;
  nxt_unit_buf_t *buf;

  char vzw_auth_token[50] = "\0";
  char vzw_m2m_token[50] = "\0";

  rc = response_init(req_info, rc, 200, TEXT_PLAIN_UTF8);
  if (rc == 1) {
    goto fail;
  }

  rc = get_vzw_tokens(&vzw_auth_token[0], &vzw_m2m_token[0]);
  if (nxt_slow_path(rc != NXT_UNIT_OK)) {
    nxt_unit_req_error(req_info, "Failed to get VZW credentials");
    goto fail;
  }

  buf = nxt_unit_response_buf_alloc(
      req_info, ((req_info->request_buf->end - req_info->request_buf->start) +
                 strlen("Hello world!\n"))
  );

  if (nxt_slow_path(buf == NULL)) {
    rc = NXT_UNIT_ERROR;
    goto fail;
  }

  p = buf->free;

  p = copy(p, "Hello world!", strlen("Hello world!"));
  *p++ = '\n';

  buf->free = p;
  rc = nxt_unit_buf_send(buf);
  if (nxt_slow_path(rc != NXT_UNIT_OK)) {
    nxt_unit_req_error(req_info, "Failed to send buffer");
    goto fail;
  }

fail:
  nxt_unit_request_done(req_info, rc);
}

void request_router(nxt_unit_request_info_t *req_info) {
  int rc;
  nxt_unit_sptr_t *rp = &req_info->request->path;

  void *path = nxt_unit_sptr_get(rp);

  if (strncmp(path, "/vzw", 4) == 0) {
    vzw_request_handler(req_info, path, rc);
  } else {
    response_init(req_info, rc, 404, TEXT_PLAIN_UTF8);
    if (rc == 1) {
      goto fail;
    }
    nxt_unit_response_write(req_info, "Error 404", strlen("Error 404"));
  }

fail:
  nxt_unit_request_done(req_info, rc);
}
