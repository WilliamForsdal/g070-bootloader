#pragma once
#include "board.h"
#include "_main.h"
#include "persistant_data.h"
#include "stm32g0xx.h"

#define BREAK __asm__("BKPT")

extern struct LinkerSymbols linkerSymbols;

void mainloop_common();

// Call this to reset CPU from software
static inline void system_reset(uint32_t reset_magic)
{
    persistantData.reset_magic_after_sw_reset = 0;            // Clear old reset reason just in case
    persistantData.reset_magic_before_sw_reset = reset_magic; // Store the new reset reason
    __NVIC_SystemReset();                                     // This does not return.
}
