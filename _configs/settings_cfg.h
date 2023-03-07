// SETTINGS_CFG_FLASH_MEM_SIZE / SETTINGS_CFG_FLASH_PAGE_SIZE
#include "_main.h"
#include "flashlowlevel/ll_flash.h" // for erase_page / write_flash
#include "sw_crc.h"  // our crc algo

// Writes to flash from settings will be aligned to this boundary (8 for STM32G070RB, 4 for GD?)
#define SETTINGS_CFG_FLASH_ALIGN     8
#define SETTINGS_CFG_FLASH_PAGE_SIZE 0x800 // 2048

#define SETTINGS_CFG_FLASH_NUM_PAGES       8                                   // we want 8 pages.
#define SETTINGS_CFG_NUM_COLLECTION_BLOCKS SETTINGS_COLLECTION_MAIN_NUM_BLOCKS // Dsg generates this

extern uint8_t _flash2[]; // linkscript defines this.
#define SETTINGS_CFG_FLASH_MEM_START ((void *)_flash2)

// Define which CRC functions to use. Must be 32-bit.
// Don't change after selecting crc-algorithm.
#define settings_crc32_init     crc32std_init
#define settings_crc32_update   crc32std_update
#define settings_crc32_finalize crc32std_finalize

// Erases a page of size SETTINGS_CFG_FLASH_PAGE_SIZE.
// signature should be:
// int erase_page(void *page_start_address) {...}
// Return < 0 if error, 0 or greater if success.
#define settings_cfg_erase_flash_page llflash_erase_page

// This function should have this signature:
// int write_flash(void *flash_address, void *data, uint32_t length) {...}
// It will always be called with flash_address aligned to SETTINGS_CFG_FLASH_ALIGN,
// however the length may be aligned to something less.
// Shuold just write 00 or FF instead of data in that case.
#define settings_cfg_write_to_flash llflash_write
