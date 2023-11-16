/** @headerfile curl_callbacks.h */
#include "curl_callbacks.h"

#include <string.h>

const size_t header_callback(
    char *buffer, size_t size, size_t nitems, void *userdata
) {
  size_t realsize = size * nitems;
  RecvData *mem = (RecvData *)userdata;

  memcpy(&(mem->response[mem->size]), buffer, realsize);
  mem->size += realsize;
  mem->response[mem->size] = 0;

  return realsize;
}

const size_t body_callback(
    void *data, size_t size, size_t nmemb, void *clientp
) {
  size_t realsize = size * nmemb;
  RecvData *mem = (RecvData *)clientp;

  memcpy(&(mem->response[mem->size]), data, realsize);
  mem->size += realsize;
  mem->response[mem->size] = 0;

  return realsize;
}
