#pragma once
#include "stm32g0xx.h"
#define IWDG_KR_ENABLE 0x0000CCCC
#define IWDG_KR_UNLOCK 0x00005555
#define IWDG_KR_KICK 0x0000AAAA

static inline void iwdg_kick() {
    IWDG->KR = IWDG_KR_KICK;
}

static inline void iwdg_init() {
    IWDG->KR = IWDG_KR_ENABLE;
    IWDG->KR = IWDG_KR_UNLOCK;
    IWDG->PR = 0x00000001; // 32000Hz / 8 = 4kHz
    IWDG->RLR = 40; // (1/4kHz) * 40 ~= 100ms
     // Wait for regs to update
    while(IWDG->SR != 0) {}
    iwdg_kick();
}
