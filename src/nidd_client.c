/** @headerfile nidd_client.h */
#include "nidd_client.h"

#include <curl/curl.h>
#include <curl/header.h>
#include <nxt_unit.h>
#include <stddef.h>
#include <string.h>

#define JSMN_HEADER

#include "curl_callbacks.h"
#include "jsmn.h"
#include "json_helpers.h"
#include "stop.h"

#define USERNAME_FIELD "\"username\":\""
#define PASSWORD_FIELD "\",\"password\":\""
#define AUTH_TOKEN_FIELD "Authorization: Basic "
#define M2M_TOKEN_FIELD "Authorization: Bearer "

char *stop_to_nidd_str(nxt_unit_request_info_t *req, Stop *stop) {}

static int extract_token(nxt_unit_request_info_t *req, char *src, char *dst) {
  static jsmn_parser p;

  /** The number of maximum possible tokens we expect in our JSON string + 1 for
   * the \0 delimiter. */
  static jsmntok_t tokens[8];

  /** The jsmn token counter. */
  static unsigned int t;

  jsmn_init(&p);

  const int ret = jsmn_parse(
      &p, src, strlen(src), tokens, sizeof(tokens) / sizeof(jsmntok_t)
  );

  if (eval_jsmn_return(req, ret)) {
    return 1;
  }

  while (t < ret) {
    if (jsoneq(src, &tokens[t], "sessionToken") ||
        jsoneq(src, &tokens[t], "access_token")) {
      strncpy(
          dst, src + tokens[t + 1].start,
          tokens[t + 1].end - tokens[t + 1].start
      );
      break;
    } else if (jsoneq(src, &tokens[t], "errorCode")) {
      nxt_unit_req_error(
          req, "Error %s: %s", src + tokens[t + 1].start,
          src + tokens[t + 3].start
      );
      return 1;
    }
    t++;
  }
  return 0;
}

int get_vzw_m2m_token(
    nxt_unit_request_info_t *req, char *username, char *password,
    char *vzw_auth_token, char *vzw_m2m_token
) {
  CURL *curl = curl_easy_init();
  CURLcode res;

  char recv_header_buf[640] = "\0";
  char recv_body_buf[192] = "\0";

  size_t post_field_size = strlen(USERNAME_FIELD) + strlen(username) +
                           strlen(PASSWORD_FIELD) + strlen(password) + 3;
  char post_field[post_field_size];

  post_field[0] = '{';
  strncpy(&post_field[1], USERNAME_FIELD, strlen(USERNAME_FIELD));
  strncpy(&post_field[strlen(USERNAME_FIELD) + 1], username, strlen(username));
  strncpy(
      &post_field[strlen(USERNAME_FIELD) + 1 + strlen(username)],
      PASSWORD_FIELD, strlen(PASSWORD_FIELD)
  );
  strncpy(
      &post_field
          [strlen(USERNAME_FIELD) + 1 + strlen(username) +
           strlen(PASSWORD_FIELD)],
      password, strlen(password)
  );
  post_field[post_field_size - 2] = '"';
  post_field[post_field_size - 1] = '}';
  post_field[post_field_size] = '\0';

  size_t header_token_field_size =
      strlen(M2M_TOKEN_FIELD) + strlen(vzw_auth_token) + 1;
  char header_token_field[header_token_field_size];

  strncpy(header_token_field, M2M_TOKEN_FIELD, strlen(M2M_TOKEN_FIELD));
  strncpy(
      &header_token_field[strlen(M2M_TOKEN_FIELD)], vzw_auth_token,
      strlen(vzw_auth_token)
  );
  header_token_field[header_token_field_size] = '\0';

  struct curl_slist *headers = NULL;
  headers = curl_slist_append(headers, "Content-Type: application/json");
  headers = curl_slist_append(headers, "Accept: application/json");
  headers = curl_slist_append(headers, header_token_field);
  curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
  curl_easy_setopt(
      curl, CURLOPT_URL,
      "https://thingspace.verizon.com/api/m2m/v1/session/login"
  );
  curl_easy_setopt(curl, CURLOPT_DEFAULT_PROTOCOL, "https");
  curl_easy_setopt(curl, CURLOPT_POST, 1L);
  curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
  curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);
  curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_field);
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, body_callback);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&recv_body_buf);
  curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, header_callback);
  curl_easy_setopt(curl, CURLOPT_HEADERDATA, (void *)&recv_header_buf);

  /* Perform the request, res will get the return code */
  res = curl_easy_perform(curl);
  /* Check for errors */
  if (res != CURLE_OK) {
    nxt_unit_req_alert(
        req, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res)
    );
  }

  res = extract_token(req, recv_body_buf, vzw_m2m_token);

  curl_slist_free_all(headers);
  curl_easy_cleanup(curl);

  return res;
}

int get_vzw_auth_token(
    nxt_unit_request_info_t *req, char *username, char *password,
    char *vzw_auth_token
) {
  CURL *curl = curl_easy_init();
  CURLcode res;

  char recv_header_buf[640] = "\0";
  char recv_body_buf[192] = "\0";

  size_t header_token_field_size =
      strlen(AUTH_TOKEN_FIELD) + strlen(vzw_auth_token) + 1;
  char header_token_field[header_token_field_size];

  strncpy(header_token_field, AUTH_TOKEN_FIELD, strlen(AUTH_TOKEN_FIELD));
  strncpy(
      &header_token_field[strlen(AUTH_TOKEN_FIELD)], vzw_auth_token,
      strlen(vzw_auth_token)
  );
  header_token_field[header_token_field_size] = '\0';

  struct curl_slist *headers = NULL;
  headers = curl_slist_append(headers, header_token_field);
  headers = curl_slist_append(
      headers, "Content-Type: application/x-www-form-urlencoded"
  );
  headers = curl_slist_append(headers, "Accept: application/json");
  curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

  curl_easy_setopt(
      curl, CURLOPT_URL, "https://thingspace.verizon.com/api/ts/v1/oauth2/token"
  );
  curl_easy_setopt(curl, CURLOPT_DEFAULT_PROTOCOL, "https");
  curl_easy_setopt(curl, CURLOPT_POST, 1L);
  curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
  curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);

  /* we want the headers be written to this file handle */
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, body_callback);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&recv_body_buf);

  /* we want the body be written to this file handle instead of stdout */
  curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, header_callback);
  curl_easy_setopt(curl, CURLOPT_HEADERDATA, (void *)&recv_header_buf);

  /* Perform the request, res will get the return code */
  res = curl_easy_perform(curl);
  /* Check for errors */
  if (res != CURLE_OK) {
    nxt_unit_req_alert(
        req, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res)
    );
  }

  res = extract_token(req, recv_body_buf, vzw_auth_token);

  curl_slist_free_all(headers);
  curl_easy_cleanup(curl);

  return res;
}
