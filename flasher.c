
#include "stm32g0xx.h"
#include "board.h"
#include "flasher.h"

#define DATA_FLASH_PHYSICAL_BLOCK_BITS 11
#define DATA_FLASH_PHYSICAL_BLOCK_SIZE (1 << DATA_FLASH_PHYSICAL_BLOCK_BITS)
#define DATA_FLASH_PHYSICAL_BLOCK_SIZE_WORDS (DATA_FLASH_PHYSICAL_BLOCK_SIZE >> 4)
#define FLASH_START 0x08000000

// get the page for the specified address
#define PAGE_FROM_ADDR(addr) ((((uint32_t)addr) - FLASH_START) >> DATA_FLASH_PHYSICAL_BLOCK_BITS)


static inline int is_addr_page_aligned(void *addr)
{
    return ((((uint32_t)addr) & (DATA_FLASH_PHYSICAL_BLOCK_SIZE - 1)) == 0);
}

static inline void wait_for_ongoing_flash_operation()
{
    // Wait for ongoing flash operation
    while (FLASH->SR & FLASH_SR_BSY1)
    {
        // wait.
    }
}

static inline void flash_unlock()
{
    FLASH->KEYR = 0x45670123;
    FLASH->KEYR = 0xCDEF89AB;
}

static inline void flash_lock()
{
    FLASH->CR |= FLASH_CR_LOCK; // Lock CR again.
}

static inline void clear_old_errors()
{
    FLASH->SR &= ~(FLASH_SR_SIZERR | FLASH_SR_PGSERR | FLASH_SR_PGAERR);
}

static inline uint32_t get_errors()
{
    return FLASH->SR & (FLASH_SR_SIZERR | FLASH_SR_PGSERR | FLASH_SR_PGAERR);
}

/// @brief Write data to flash AFTER it's erased.
/// @param flash Where to write.
/// @param data What to write.
/// @param length How many bytes, aligned to 4.
/// @return
int RAMFUNC write_flash(void *flash, const void *data, uint32_t length_bytes)
{
    if ((length_bytes & 3) != 0)
    {
        return -1; // bad length.
    }
    if (((uint32_t)flash & 7) != 0)
    {
        return -1; // bad length.
    }
    uint32_t length_words = length_bytes >> 2; // divide by 4
    uint32_t *flash_ptr = (uint32_t *)flash;
    uint32_t *data_ptr = (uint32_t *)data;
    wait_for_ongoing_flash_operation();
    flash_unlock();
    clear_old_errors();
    FLASH->CR |= FLASH_CR_PG;
    while (length_words)
    {
        *(flash_ptr)++ = *data_ptr++; // Write the first word
        length_words--;
        if (length_words)
        {
            *flash_ptr++ = *data_ptr++; // Write the second word
            length_words--;
        }
        else
        {
            *flash_ptr++ = 0xffffffff;
        }
        wait_for_ongoing_flash_operation();

        uint32_t errors = get_errors();
        if (errors != 0)
        {
            return -2;
        }

        // EOP is only set if end of operation interrupts are enabled.
        if (FLASH->SR & FLASH_SR_EOP)
        {
            // Ok, clear it.
            // Clear by writing 1!
            FLASH->SR |= FLASH_SR_EOP;
        }
    }
    FLASH->CR &= ~FLASH_CR_PG;
    flash_lock();
    return 1;
}

/// @brief Erase a flash page.
/// @param page_start_addr The start addr of the page, ie aligned to 0x800
/// @return 0 if fail, positive if success.
int RAMFUNC erase_page(void *page_addr)
{
    uint32_t page_idx = PAGE_FROM_ADDR(page_addr);
    wait_for_ongoing_flash_operation();
    flash_unlock();
    // Set which page to flash and set PER (to erase page)
    FLASH->CR = (FLASH->CR & (~(FLASH_CR_PNB))) | (page_idx << FLASH_CR_PNB_Pos) | FLASH_CR_PER;
    FLASH->CR |= FLASH_CR_STRT; // Start erase

    LED_ON();
    wait_for_ongoing_flash_operation();
    LED_OFF();

    FLASH->CR &= ~FLASH_CR_PER; // Clear erase flag

    flash_lock();

    return 1;
}

/// @brief Erase and flash.
/// @param flash Where to erase and flash
/// @param data The data to write
/// @param length Length (WORDS) of data to flash, double-word aligned (ie even: 2,4,6..).
/// @return 0 if fail, 1 success.
int RAMFUNC erase_and_flash(void *flash, const void *data, uint32_t length_bytes, int reset_after)
{
    if (length_bytes == 0)
    {
        return 1; // I guess it worked if we didn't want to write anything?
    }
    if ((length_bytes & 7) != 0)
    {
        return -1; // bad length.
    }
    if (!is_addr_page_aligned(flash))
    {
        return -1;
    }

    // First erase all pages
    int num_pages_to_erase = (((length_bytes)-1) >> DATA_FLASH_PHYSICAL_BLOCK_BITS) + 1;
    uint32_t *flash_page_addr = (uint32_t *)flash;
    while (num_pages_to_erase--)
    {
        erase_page(flash_page_addr);
        flash_page_addr += DATA_FLASH_PHYSICAL_BLOCK_SIZE_WORDS;
    }

    // Now write data to flash
    write_flash(flash, data, length_bytes);
    if (reset_after)
    {
        NVIC_SystemReset();
        while(1) {}; // above func doesn't return.
    }
    return 1; // OK
}
