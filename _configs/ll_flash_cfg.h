#pragma once
#include "stm32g0xx.h"
#include "board.h"

// Define how to kick watchdog
#define LL_FLASH_WD_RESET __NOP // TODO implement watchdog

// Where to place flash functions
#define SECTION_LL_FLASH_RAM SECTION_RAMFUNC
