/** @file nidd_client.h
 *  @brief Function definitions for user defined curl callback functions.
 */
#ifndef CURL_CALLBACKS_H
#define CURL_CALLBACKS_H
#include <curl/curl.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"

typedef struct RecvData {
  char *response;
  size_t size;
} RecvData;

/** @fn const size_t mem_write_callback(const char *buffer, const size_t size,
 * size_t nitems, const void *userdata);
 *  @brief User defined curl callback for writing response data to stack mem.
 */
size_t mem_write_callback(
    const char *buffer, const size_t size, const size_t nitems,
    const void *userdata
);

// typedef struct RecvData {
//   char *memory;
//   size_t size;
// } RecvData;

// static const size_t mem_cb(
//     const void *contents, const size_t size, const size_t nmemb,
//     const void *userp
// ) {
//   size_t realsize = size * nmemb;
//   struct RecvData *mem = (struct RecvData *)userp;

//   char *ptr = realloc(mem->memory, mem->size + realsize + 1);
//   if (!ptr) {
//     /* out of memory! */
//     printf("not enough memory (realloc returned NULL)\n");
//     return 0;
//   }

//   mem->memory = ptr;
//   memcpy(&(mem->memory[mem->size]), contents, realsize);
//   mem->size += realsize;
//   mem->memory[mem->size] = 0;

//   return realsize;
// }
#endif
