
/*
 * Copyright (C) NGINX, Inc.
 */

#include <nxt_clang.h>
#include <nxt_unit.h>
#include <nxt_unit_request.h>

// #include "../include/nxt_unit.h"
// #include "../include/nxt_unit_request.h"
// #include "../include/nxt_clang.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "stop.h"
/*#include "jsmn_parse.h"*/
#include "custom_http_client.h"

#define CONTENT_TYPE "Content-Type"
#define TEXT_PLAIN "text/plain; charset=utf-8"
#define JSON_UTF8 "application/json; charset=utf-8"

static int thread_count;
static pthread_t *threads;

static unsigned int minutes_to_departure(Departure *departure) {
  int edt_ms = departure->etd;
  struct timespec ts;
  timespec_get(&ts, TIME_UTC);
  return (unsigned int)(edt_ms - (ts.tv_nsec / 1000)) / 60;
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

static void app_request_handler(nxt_unit_request_info_t *req) {
  int rc;
  char *p;
  ssize_t res;
  nxt_unit_buf_t *buf;

  rc = nxt_unit_response_init(
      req, 200 /* Status code. */, 1 /* Number of response headers. */,
      nxt_length(CONTENT_TYPE) + nxt_length(TEXT_PLAIN)
  );
  if (nxt_slow_path(rc != NXT_UNIT_OK)) {
    printf("nxt_unit_response_init failed");
    goto fail;
  }

  rc = nxt_unit_response_add_field(
      req, CONTENT_TYPE, nxt_length(CONTENT_TYPE), TEXT_PLAIN,
      nxt_length(TEXT_PLAIN)
  );
  if (nxt_slow_path(rc != NXT_UNIT_OK)) {
    printf("nxt_unit_response_add_field failed");
    goto fail;
  }

  rc = nxt_unit_response_send(req);
  if (nxt_slow_path(rc != NXT_UNIT_OK)) {
    printf("first nxt_unit_response_send failed");
    goto fail;
  }

  rc = http_request_routes();
  if (nxt_slow_path(rc != NXT_UNIT_OK)) {
    printf("http_request_routes failed");
    goto fail;
  }

  buf = nxt_unit_response_buf_alloc(
      req,
      (req->request_buf->end - req->request_buf->start) + strlen(recv_body_buf)
  );

  if (nxt_slow_path(buf == NULL)) {
    rc = NXT_UNIT_ERROR;
    goto fail;
  }

  p = buf->free;
  p = copy(p, recv_body_buf, strlen(recv_body_buf));

  buf->free = p;

  rc = nxt_unit_buf_send(buf);

fail:
  nxt_unit_request_done(req, rc);
}

int main(int argc, char **argv) {
  int i, err;
  nxt_unit_ctx_t *ctx;
  nxt_unit_init_t init;

  /*static Stop stop = {.last_updated = 0, .id = STOP_ID};*/

  if (argc == 3 && strcmp(argv[1], "-t") == 0) {
    thread_count = atoi(argv[2]);
  }

  memset(&init, 0, sizeof(nxt_unit_init_t));

  init.callbacks.request_handler = app_request_handler;
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

  nxt_unit_debug(NULL, "main worker done");

  return 0;
}
