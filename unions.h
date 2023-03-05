#include <stdint.h>
// unions.h - helper unions

union UUnsigned32Bits
{
    uint8_t u8[4];
    uint16_t u16[2];
    uint32_t u32;
};


union U32Bits
{
    int8_t i8[4];
    int16_t i16[2];
    int32_t i32;
    uint8_t u8[4];
    uint16_t u16[2];
    uint32_t u32;
};

union UPtrs
{
    void *v;
    int8_t *i8;
    int16_t *i16;
    int32_t *i32;
    uint8_t *u8;
    uint16_t *u16;
    uint32_t *u32;
};

union UConstPtrs
{
    const void *v;
    const int8_t *i8;
    const int16_t *i16;
    const int32_t *i32;
    const uint8_t *u8;
    const uint16_t *u16;
    const uint32_t *u32;
};
