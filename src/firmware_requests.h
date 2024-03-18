/** @file firmware_requests.h
 *  @brief Macro and function defines for iot firmware related requests.
 */

#ifndef FIRMWARE_REQUESTS_H
#define FIRMWARE_REQUESTS_H

/** @fn int firmware_versions(void)
 *  @brief Gets a list of github release tags using the github-api.
 */
int latest_firmware(char *tags_buf);

/** @fn firmware_update()
 *  @brief Proxys a firmware download octect-stream from github objects.
 */
// int firmware_update();
#endif
