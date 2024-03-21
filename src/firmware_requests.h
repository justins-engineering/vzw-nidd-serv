/** @file firmware_requests.h
 *  @brief Macro and function defines for iot firmware related requests.
 */

#ifndef FIRMWARE_REQUESTS_H
#define FIRMWARE_REQUESTS_H

#include <stdio.h>
#include <sys/stat.h>

/** @fn int latest_firmware(char *tags_buf)
 *  @brief Gets a list of github release tags using the github-api.
 */
// int latest_firmware_tag(char *tags_buf);

/** @fn int update_firmware_github(char *tag, char *buf);
 *  @brief Proxys a firmware download octect-stream from github objects.
 */
int download_firmware_github(FILE **fptr, long *file_size);
#endif
