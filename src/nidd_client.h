/** @file nidd_client.h
 *  @brief Macro and function defines for the NIDD client.
 */

#ifndef NIDD_CLIENT_H
#define NIDD_CLIENT_H
#include <nxt_unit.h>

#include "stop.h"

#define VZW_PUB_KEY "bc9247a8-82e9-4aab-9a42-0711d91fc123"

/** @fn int stop_to_nidd(nxt_unit_request_info_t* req, Stop* stop)
 *  @brief Transforms the Stop departure info into a NIDD message.
 */
char *stop_to_nidd(nxt_unit_request_info_t *req, Stop *stop);

int get_vzw_auth_token(
    nxt_unit_request_info_t *req, char *username, char *password,
    char *vzw_auth_token
);

int get_vzw_m2m_token(
    nxt_unit_request_info_t *req, char *username, char *password,
    char *vzw_auth_token, char *vzw_m2m_token
);
#endif
