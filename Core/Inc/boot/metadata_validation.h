#ifndef METADATA_VALIDATION_H
#define METADATA_VALIDATION_H

#include <stdint.h>
#include "ota_metadata.h"

uint8_t ValidateMetadata(const OTA_Metadata_t *metadata);

#endif
