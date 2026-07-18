#ifndef MCU_VALIDATION_H
#define MCU_VALIDATION_H

#include <stdint.h>
#include "ota_metadata.h"

uint8_t ValidateMCU(
        const OTA_Metadata_t *metadata);

#endif
