// SETTINGS_CFG_FLASH_MEM_SIZE / SETTINGS_CFG_FLASH_PAGE_SIZE
#include "sw_crc.h" // crc algo
#include "_main.h"

#define SETTINGS_CFG_FLASH_PAGE_SIZE            0x800 // 2048
#define SETTINGS_CFG_FLASH_MEM_SIZE             SETTINGS_CFG_FLASH_PAGE_SIZE * 8
#define SETTINGS_CFG_NUM_COLLECTION_BLOCKS      SETTINGS_COLLECTION_MAIN_NUM_BLOCKS
#define FLASH_START                             0x08000000
#define SETTINGS_CFG_START_PAGE                 32
#define SETTINGS_CFG_FLASH_MEM_START            ((void *)(FLASH_START + (SETTINGS_CFG_FLASH_PAGE_SIZE * SETTINGS_CFG_START_PAGE)))
// Define which functions to use
#define settings_crc32_init             crc32std_init
#define settings_crc32_update           crc32std_update
#define settings_crc32_finalize         crc32std_finalize
#define settings_cfg_erase_flash_page   erase_page
#define settings_cfg_write_to_flash     write_flash

// settings_cfg_write_to_flash(flash_addr, ((uint8_t *) &header), sizeof(struct SettingsBlockHeader))