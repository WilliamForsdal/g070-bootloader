#pragma once
#include <stdint.h>
#include "stm32g0xx.h"

#define CLOCK_SPEED 16000000
#define SYSTICK_FRQ 1000
#define SYSTICK_TICKS_PER_1KHZ (CLOCK_SPEED / SYSTICK_FRQ) - 1

// 1ms counter
extern volatile uint32_t systick_counter;

__WEAK void iwdg_kick() { }

#define SYSTICK_DELAY_MS(t)                 \
    do                                      \
    {                                       \
        uint32_t tmo = systick_counter + t; \
        while (systick_counter < tmo)       \
        {                                   \
            iwdg_kick();                    \
        }                                   \
    } while (0)

static inline uint32_t get_systick()
{
    return systick_counter;
}

#define TMR_IS_TIMEOUT(tmo)    (systick_counter >= tmo)
#define TMR_CALC_TMO_TICK(tmo) (systick_counter + tmo)