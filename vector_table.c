#include <stdint.h>

extern const uint8_t _estack[];

extern void reset_handler(void);

struct VectorTable {
    uint32_t stackpointer;
    void (*reset_handler)(void);

};


volatile const struct VectorTable vector_table = {
    .stackpointer = (uint32_t)_estack,
    .reset_handler = reset_handler
};