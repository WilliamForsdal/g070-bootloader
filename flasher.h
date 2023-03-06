#pragma once
#include <stdint.h>

#define RAMFUNC __attribute__((section(".RamFunc")))
#define ADDR_FROM_PAGE(page)    ((void *)(0x08000000 + 0x800*page))
// These functions are RAMFUNCs,
#define WAIT_FOR_ONGOING_FLASH_OPERATION() do { } while(FLASH->SR & FLASH_SR_BSY1)

int RAMFUNC write_flash(void *flash, const void *data, uint32_t length_bytes);
int RAMFUNC erase_and_flash(void *flash, const void *data, uint32_t length_bytes, int reset_after);


int RAMFUNC erase_page(void *page_addr);