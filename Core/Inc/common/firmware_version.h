#ifndef FIRMWARE_VERSION_H
#define FIRMWARE_VERSION_H

#include <stdint.h>

#define FIRMWARE_VERSION_LENGTH    32

void FirmwareVersion_GetCurrent(
        char *version);

void FirmwareVersion_SetCurrent(
        const char *version);

#endif
