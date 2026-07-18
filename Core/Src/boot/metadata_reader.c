#include "metadata_reader.h"
#include "w25q128.h"
#include "ota_config.h"

void OTA_ReadMetadata(OTA_Metadata_t *metadata)
{
    W25Q128_ReadData(
            OTA_METADATA_ADDRESS,
            (uint8_t*)metadata,
            sizeof(OTA_Metadata_t));
}
