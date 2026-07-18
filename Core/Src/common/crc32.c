#include "crc32.h"

uint32_t CRC32_Calculate(const uint8_t *data,
                         uint32_t length)
{
    uint32_t crc = 0xFFFFFFFF;

    for(uint32_t i = 0; i < length; i++)
    {
        crc ^= data[i];

        for(uint32_t j = 0; j < 8; j++)
        {
            if(crc & 1)
            {
                crc = (crc >> 1) ^ 0xEDB88320;
            }
            else
            {
                crc >>= 1;
            }
        }
    }

    return ~crc;
}
