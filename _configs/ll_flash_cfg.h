#pragma once
#include "stm32g0xx.h"

// Define how to kick watchdog
#define LL_FLASH_WD_RESET __NOP  // TODO implement watchdog

// Where to place flash functions
#define SECTION_LL_FLASH_RAM __attribute__((section(".RamFunc"), noinline))
