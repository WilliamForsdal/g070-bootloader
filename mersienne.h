#pragma once 
#include <stdint.h>

// mersienne.c

static inline uint32_t mod255(uint32_t nr)
{
    nr = (nr >> 16) + (nr & 0xFFFF);
    nr = (nr >>  8) + (nr & 0xFF);
    if (nr < 255) {
        return nr;
    }
    if (nr < 2*255) {
        return nr - 255;
    }
    return nr - 2*255;
}

static inline uint32_t mod65535(uint32_t nr)
{
    nr = (nr >> 16) + (nr & 0xFFFF);
    if (nr < 65535) {
        return nr;
    }
    if (nr < 2*65535) {
        return nr - 65535;
    }
    return nr - 2*65535;
}
