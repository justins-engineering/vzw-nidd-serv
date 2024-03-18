/** @headerfile vzw_connect.h */
#include "firmware_requests.h"

#include <config.h>
#include <curl/curl.h>
#include <curl/header.h>
#include <string.h>

#include "curl_callbacks.h"

#define REC_BUF_SIZE 2048
#define REC_HEADER_SIZE 5000

#define REPO "umts/embedded-departure-board"

static void latest_version(char *headers, char *tag) {
  char *p;
  p = strstr(headers, "location:");
  p += 9;
  p = strstr(p, "tag/");
  p += 4;

  int tag_size = (strstr(p, "\r\n") - p);
  memcpy(tag, p, tag_size);
  *(tag + tag_size) = '\0';
}

int latest_firmware(char *latest_tag) {
  CURL *curl = curl_easy_init();
  CURLcode res;

  char header_buf[REC_HEADER_SIZE];

  char agent[19] = "licurl/";

  RecvData header_data = {header_buf, 0};

  curl_easy_setopt(curl, CURLOPT_DEFAULT_PROTOCOL, "https");
  curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
  curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
  curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);
  curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1L);
  curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 0L);
  curl_easy_setopt(curl, CURLOPT_NOBODY, 1L);

  curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, mem_write_callback);
  curl_easy_setopt(curl, CURLOPT_HEADERDATA, &header_data);

  curl_easy_setopt(
      curl, CURLOPT_URL, "https://github.com/" REPO "/releases/latest"
  );
  curl_easy_setopt(
      curl, CURLOPT_USERAGENT,
      strcat(agent, curl_version_info(CURLVERSION_NOW)->version)
  );

  res = curl_easy_perform(curl);
  if (res != CURLE_OK) {
    PRINTERR("curl_easy_perform() failed: %s", curl_easy_strerror(res));
    goto fail;
  }

fail:
  curl_easy_cleanup(curl);

  latest_version(header_buf, latest_tag);
  PRINTDBG("\n%s\n", latest_tag);

  return (int)res;
}
