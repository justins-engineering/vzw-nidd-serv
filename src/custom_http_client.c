/** @headerfile custom_http_client.h */
#include "custom_http_client.h"

/* Newlib C includes */
#include <stdbool.h>
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

/** @def HTTP_REQUEST_HEADERS
 *  @brief A macro that defines the HTTP request headers for the GET request.
 */
/*#define HTTP_REQUEST_HEADERS                   \*/
  /*"GET " HTTP_REQUEST_PATH                     \*/
  /*" HTTP/1.1\r\n"                              \*/
  /*"Host: " HTTP_REQUEST_HOSTNAME ":" HTTP_PORT \*/
  /*"\r\n"                                       \*/
  /*"Accept: application/json\r\n"               \*/
  /*"Connection: close\r\n\r\n"*/

/** @def RECV_HEADER_BUF_SIZE
 *  @brief A macro that defines the max size for HTTP response headers receive buffer.
 *
 *  Seems to be ~320 bytes, size ~doubled for safety.
 */
#define RECV_HEADER_BUF_SIZE 600

/*#define HTTP_REQUEST_HEAD_LEN (sizeof(HTTP_REQUEST_HEADERS) - 1)*/

/** HTTP send buffer defined by the HTTP_REQUEST_HEADERS macro. */
/*static const char send_buf[] = HTTP_REQUEST_HEADERS;*/

/** HTTP response headers buffer with size defined by the RECV_HEADER_BUF_SIZE macro. */
static char recv_headers_buf[RECV_HEADER_BUF_SIZE] = "\0";

/** HTTP response body buffer with size defined by the RECV_BODY_BUF_SIZE macro. */
char recv_body_buf[RECV_BODY_BUF_SIZE] = "\0";

/** Godaddy server ca certificate */
/*static const char ca_cert[] = {*/
	/*#include "../cert/gdig2.crt.pem"*/
/*};*/

/*static const char pvta_cert[] = {*/
	/*#include "../cert/pvta-com.pem"*/
/*};*/

int http_request_routes(void) {
  CURL *curl = curl_easy_init();
  CURLcode res;

  struct curl_slist *chunk = NULL;
  chunk = curl_slist_append(chunk, "Accept: application/json");
  curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);

  curl_easy_setopt(curl, CURLOPT_URL, URL);
  curl_easy_setopt(curl, CURLOPT_DEFAULT_PROTOCOL, "https");

  curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
  curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
  curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
  /* we want the headers be written to this file handle */
  curl_easy_setopt(curl, CURLOPT_HEADERDATA, recv_headers_buf);

  /* we want the body be written to this file handle instead of stdout */
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, recv_body_buf);

  curl_easy_setopt(curl, CURLOPT_SSLCERTTYPE, "PEM");
  curl_easy_setopt(curl, CURLOPT_SSLCERT, "../cert/pvta-com.pem");
  curl_easy_setopt(curl, CURLOPT_CAINFO, "../cert/gdig2.crt.pem");
  curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);

  /* Perform the request, res will get the return code */
  res = curl_easy_perform(curl);
  /* Check for errors */
  if (res != CURLE_OK) {
    fprintf(stderr, "curl_easy_perform() failed: %s\n",
        curl_easy_strerror(res));
  }

  /* always cleanup */
  curl_easy_cleanup(curl);

  return res;
}
