#pragma once
#include "stm32g0xx.h"
#define IWDG_KR_ENABLE 0x0000CCCC
#define IWDG_KR_UNLOCK 0x00005555
#define IWDG_KR_KICK 0x0000AAAA

static inline void iwdg_kick() {
    IWDG->KR = IWDG_KR_KICK;
}
