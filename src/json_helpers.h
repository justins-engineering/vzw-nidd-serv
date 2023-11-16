/** @file json_helpers.h
 *  @brief Macro and function defines for the NIDD client.
 */

#ifndef JSON_HELPERS_H
#define JSON_HELPERS_H

#define JSMN_HEADER

#include <nxt_unit.h>
#include <string.h>

#include "jsmn.h"

/** Compares a string with a jsmn token value. */
const int jsoneq(const char *json_ptr, jsmntok_t *tok, const char *string);

const int eval_jsmn_return(nxt_unit_request_info_t *req, int ret);
#endif
