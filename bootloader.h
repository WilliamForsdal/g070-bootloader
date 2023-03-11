#pragma once

#include "board.h"
#include "flashlowlevel/ll_flash.h"

/// @brief Does not return. can only leave bootloader by reset.
void SECTION_RAMFUNC bootloader();