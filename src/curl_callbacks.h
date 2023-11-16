/** @file nidd_client.h
 *  @brief Function definitions for user defined curl callback functions.
 */
#ifndef CURL_CALLBACKS_H
#define CURL_CALLBACKS_H
#include <curl/curl.h>

typedef struct RecvData {
  char *response;
  size_t size;
} RecvData;

/** @fn const size_t header_callback(void *data, char *buffer, size_t size,
 * size_t nitems, void *userdata);
 *  @brief User defined curl callback for writing response headers.
 */
size_t header_callback(
    char *buffer, size_t size, size_t nitems, void *userdata
);

/** @fn const size_t body_callback(void *data, size_t size, size_t nmemb, void
 * *clientp);
 *  @brief User defined curl callback for writing response body.
 */
size_t body_callback(void *data, size_t size, size_t nmemb, void *clientp);
#endif
