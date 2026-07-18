#ifndef FIRMWARE_SIZE_VALIDATION_H
#define FIRMWARE_SIZE_VALIDATION_H

#include <stdint.h>
#include "ota_metadata.h"

uint8_t ValidateFirmwareSize(
        const OTA_Metadata_t *metadata);

#endif
