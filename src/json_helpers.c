/** @headerfile json_helpers.h */
#include "json_helpers.h"

int jsoneq(const char *json_ptr, jsmntok_t *tok, const char *string) {
  if (tok->type == JSMN_STRING &&
      (int)strlen(string) == tok->end - tok->start &&
      strncmp(json_ptr + tok->start, string, tok->end - tok->start) == 0) {
    return 1;
  }
  return 0;
}

int eval_jsmn_return(nxt_unit_request_info_t *req, int ret) {
  switch (ret) {
    case 0:
      nxt_unit_req_error(req, "Parsed Empty JSON string.");
      return 1;
    case JSMN_ERROR_NOMEM:
      nxt_unit_req_error(
          req, "Failed to parse JSON; Not enough tokens were provided."
      );
      return 1;
    case JSMN_ERROR_INVAL:
      nxt_unit_req_error(
          req, "Failed to parse JSON; Invalid character inside JSON string."
      );
      return 1;
    case JSMN_ERROR_PART:
      nxt_unit_req_error(
          req,
          "Failed to parse JSON; The string is not a full JSON packet, more "
          "bytes expected."
      );
      return 1;
    default:
      nxt_unit_req_log(
          req, NXT_UNIT_LOG_INFO, "Tokens allocated: %d/%d\n", ret, 8
      );
      return 0;
  }
}
