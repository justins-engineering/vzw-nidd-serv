/** @headerfile custom_http_client.h */
#include "custom_http_client.h"

/* Newlib C includes */
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

/** A macro that defines the HTTP request host name for the request headers. */
#define HTTP_REQUEST_HOSTNAME "bustracker.pvta.com"

/** A macro that defines the HTTP file path for the request headers. */
#define HTTP_REQUEST_PATH \
  "/InfoPoint/rest/SignageStopDepartures/GetSignageDeparturesByStopId?stopId=" STOP_ID

#define URL \
  "https://" HTTP_REQUEST_HOSTNAME HTTP_REQUEST_PATH

/** A macro that defines the HTTP port for the request headers. */
#if defined(CONFIG_NET_SOCKETS_SOCKOPT_TLS)
#define HTTP_PORT "443"
#else
#define HTTP_PORT "80"
#endif

/** @def RECV_HEADER_BUF_SIZE
 *  @brief A macro that defines the max size for HTTP response headers receive buffer.
 *
 *  Seems to be ~320 bytes, size ~doubled for safety.
 */
#define RECV_HEADER_BUF_SIZE 600

/** HTTP response headers buffer with size defined by the RECV_HEADER_BUF_SIZE macro. */
static char recv_headers_buf[RECV_HEADER_BUF_SIZE] = "\0";

/** HTTP response body buffer with size defined by the RECV_BODY_BUF_SIZE macro. */
char recv_body_buf[RECV_BODY_BUF_SIZE] = "\0";

struct RecvData {
  char *response;
  size_t size;
};

struct RecvData recv_body = { recv_body_buf, 0};
struct RecvData recv_headers = { recv_headers_buf, 0};

size_t header_callback(char *buffer, size_t size, size_t nitems, void *userdata) {
  size_t realsize = size * nitems;
  struct RecvData *mem = (struct RecvData *)userdata;

  memcpy(&(mem->response[mem->size]), buffer, realsize);
  mem->size += realsize;
  mem->response[mem->size] = 0;

  fprintf(stdout, "%s\n", mem->response);

  return realsize;
}

static size_t cb(void *data, size_t size, size_t nmemb, void *clientp) {
  size_t realsize = size * nmemb;
  struct RecvData *mem = (struct RecvData *)clientp;

  memcpy(&(mem->response[mem->size]), data, realsize);
  mem->size += realsize;
  mem->response[mem->size] = 0;

  fprintf(stdout, "%s\n", mem->response);

  return realsize;
}

int http_request_routes(void) {
  CURL *curl = curl_easy_init();
  CURLcode res;

  struct curl_slist *header = NULL;
  header = curl_slist_append(header, "Accept: application/json");
  curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header);

  curl_easy_setopt(curl, CURLOPT_URL, URL);
  curl_easy_setopt(curl, CURLOPT_DEFAULT_PROTOCOL, "https");

  /*curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);*/
  curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
  curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

  /* we want the headers be written to this file handle */
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, cb);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&recv_body);

  /* we want the body be written to this file handle instead of stdout */
  curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, header_callback);
  curl_easy_setopt(curl, CURLOPT_HEADERDATA, (void *)&recv_headers);

  /*curl_easy_setopt(curl, CURLOPT_SSLCERTTYPE, "PEM");*/
  /*curl_easy_setopt(curl, CURLOPT_SSLCERT, "/srv/cert/");*/
  curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);

  /* Perform the request, res will get the return code */
  res = curl_easy_perform(curl);
  /* Check for errors */
  if (res != CURLE_OK) {
    fprintf(stderr, "curl_easy_perform() failed: %s\n",
        curl_easy_strerror(res));
  }

  /*fprintf(stdout, "%s\n", recv_headers_buf);*/
  /*fprintf(stdout, "%s\n", recv_body_buf);*/

  /* always cleanup */
  curl_easy_cleanup(curl);

  return res;
}
