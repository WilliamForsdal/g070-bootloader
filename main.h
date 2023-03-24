#pragma once
#include "board.h"
#include "_main.h"
#include "persistant_data.h"
#include "stm32g0xx.h"

#define NULL  (0)
#define BREAK __asm__("BKPT")

struct LinkerSymbols {
    uint32_t *start_text_flash;
    uint32_t *end_text_flash;

    uint32_t *start_ram_data;
    uint32_t *end_ram_data;

    uint32_t *start_ram_bss;
    uint32_t *end_ram_bss;

    uint32_t *start_ram_persistant;
    uint32_t *end_ram_persistant;

    uint32_t *extbuf_start;
    uint32_t *extbuf_end;
    uint32_t extbuf_size; // end - start
};

extern struct LinkerSymbols linkerSymbols;

void mainloop_common();

// Call this to reset CPU from software
static inline void system_reset(uint32_t reset_magic)
{
    persistantData.reset_magic_after_sw_reset = 0;            // Clear old reset reason just in case
    persistantData.reset_magic_before_sw_reset = reset_magic; // Store the new reset reason
    __NVIC_SystemReset();                                     // This does not return.
}
