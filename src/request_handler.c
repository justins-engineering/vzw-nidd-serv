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
#include "json_helpers.h"
#include "vzw_connect.h"

#define CONTENT_TYPE "Content-Type"
#define TEXT_PLAIN "text/plain; charset=utf-8"

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

void request_handler(nxt_unit_request_info_t *req) {
  int rc;
  char *p;
  // ssize_t res;
  nxt_unit_buf_t *buf;

  char vzw_auth_token[50] = "\0";
  char vzw_m2m_token[50] = "\0";

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

  rc = get_vzw_tokens(&vzw_auth_token[0], &vzw_m2m_token[0]);
  if (nxt_slow_path(rc != NXT_UNIT_OK)) {
    nxt_unit_req_error(req, "Failed to get VZW credentials");
    goto fail;
  }

  buf = nxt_unit_response_buf_alloc(
      req, ((req->request_buf->end - req->request_buf->start) +
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
    nxt_unit_req_error(req, "Failed to send buffer");
    goto fail;
  }

fail:
  nxt_unit_request_done(req, rc);
}
