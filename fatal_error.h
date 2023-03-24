#pragma once
#include "cmsis_gcc.h"
#include "main.h"
#include "iwdg.h"

static inline void fatal_error_no_ret(uint32_t error_code) 
{
    __disable_irq();
    persistantData.main_state.state = DSG_ENUM_MAIN_STATE_FATAL_ERROR;
    BREAK;
    __IO uint32_t error = error_code;
    (void)error;
    while (1)
    {
        iwdg_kick();
        mainloop_common();
    }
}