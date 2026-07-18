#ifndef OTA_FLAG_H
#define OTA_FLAG_H

#include <stdint.h>

uint8_t OTA_IsUpdatePending(void);

void OTA_SetUpdatePending(void);

void OTA_ClearUpdatePending(void);

#endif
