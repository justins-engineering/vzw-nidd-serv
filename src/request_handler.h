/** @file request_handler.h
 *  @brief Macro and function defines for the stop_request_handler.
 */

#ifndef REQUEST_HANDLER_H
#define REQUEST_HANDLER_H
#include <nxt_unit.h>

/** @fn void stop_request_handler(nxt_unit_request_info_t *req)
 *  @brief Unit request handler for a stop request.
 */
void request_handler(nxt_unit_request_info_t *req);
#endif
