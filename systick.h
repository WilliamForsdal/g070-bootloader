#pragma once
#include <stdint.h>
#include "stm32g0xx.h"
#include "iwdg.h"
#include "board.h"
#include "persistant_data.h"

#define CLOCK_SPEED            16000000
#define SYSTICK_FRQ            1000
#define SYSTICK_TICKS_PER_1KHZ (CLOCK_SPEED / SYSTICK_FRQ) - 1

#define SYSTICK_COUNTER (persistantData.main_state.systick_counter)

#define SYSTICK_DELAY_MS(t)                                                                                                                                                                            \
    do {                                                                                                                                                                                               \
        uint32_t tmo = SYSTICK_COUNTER + t;                                                                                                                                                            \
        while (SYSTICK_COUNTER < tmo) {                                                                                                                                                                \
            iwdg_kick();                                                                                                                                                                               \
        }                                                                                                                                                                                              \
    } while (0)

static inline void systick_init()
{
    SysTick->LOAD = (uint32_t)(SYSTICK_TICKS_PER_1KHZ);
    NVIC_SetPriority(SysTick_IRQn, (1UL << __NVIC_PRIO_BITS) - 1UL);
    SysTick->VAL = 0UL;
    SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;
}

static inline uint32_t get_systick() { return SYSTICK_COUNTER; }

#define TMR_IS_TIMEOUT(tmo)    (SYSTICK_COUNTER >= tmo)
#define TMR_CALC_TMO_TICK(tmo) (SYSTICK_COUNTER + tmo)