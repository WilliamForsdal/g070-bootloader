#pragma once
#include <stdint.h>

#define crc32std_init() (0xffffffff)
#define crc32std_finalize(crc) (crc ^ 0xffffffff)

typedef uint32_t crc32std_t;
crc32std_t crc32std_update(crc32std_t crc, const void *data, uint32_t data_len);
