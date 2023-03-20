#include "main.h"
#include "flashlowlevel/ll_flash.h"
#include "jabus.h"
#include "stm32g0xx_ll_gpio.h"
#include "stm32g0xx_ll_rcc.h"
#include "stm32g0xx_ll_utils.h"

#include "init.h"
#include "settings/settings.h"
#include "systick.h"
#include "uart1.h"

#define PERSISTANT_MAGIC 0xb41e6ea0
struct PersistantDataSingleton SECTION_PERSISTANT_RAM persistantData;

struct LinkerSymbols linkerSymbols;

void save_startup_reason_copy_vars();
void check_startup_reason_and_reply();
void loop();

void HardFault_Handler()
{
    BREAK;
    while (1) {
        LED_ON();
    }
}

int main(void)
{
    // BREAK;
    save_startup_reason_copy_vars();
    
    // Initialize oscillator, timers and peripherals
    setup_normal_mode();
    
    // init settings
    settings_init();

    if(persistantData.reset_magic_after_reset != 0) {
        js.buf->header.dst = 0;
        js.buf->header.length = sizeof(struct JabusAnswerReset);
        js.buf->header.cmd = JABUS_CMD_RESET;
        struct JabusAnswerReset *rst_cmd = &js.buf->cmds.ansReset;
        rst_cmd->current_mode_magic = persistantData.reset_magic_after_reset;
        send_jabus_ans();
    }

    // Main loop
    while (1) {
        loop();
    }
    return 0;
}

void save_startup_reason_copy_vars()
{
    extern uint8_t _stext[];
    extern uint8_t _etext[];
    extern uint8_t _sdata[];
    extern uint8_t _edata[];
    extern uint8_t _sbss[];
    extern uint8_t _ebss[];
    extern uint8_t _start_persistant[];
    extern uint8_t _end_persistant[];
    extern uint8_t _extbuf_start[];
    extern uint8_t _extbuf_end[];
    extern uint8_t _extbuf_size[];
    linkerSymbols.start_text_flash = (uint32_t *)_stext;
    linkerSymbols.end_text_flash = (uint32_t *)_etext;
    linkerSymbols.start_ram_data = (uint32_t *)_sdata;
    linkerSymbols.end_ram_data = (uint32_t *)_edata;
    linkerSymbols.start_ram_bss = (uint32_t *)_sbss;
    linkerSymbols.end_ram_bss = (uint32_t *)_ebss;
    linkerSymbols.start_ram_persistant = (uint32_t *)_start_persistant;
    linkerSymbols.end_ram_persistant = (uint32_t *)_end_persistant;
    linkerSymbols.extbuf_start = (uint32_t *)_extbuf_start;
    linkerSymbols.extbuf_end = (uint32_t *)_extbuf_end;
    linkerSymbols.extbuf_size = (uint32_t)_extbuf_size;

    // If first start, reset_counter will be set to 0 later.
    // If sw reset or other reset, this counter will increase.
    persistantData.reset_counter++;
    if (persistantData.magic != PERSISTANT_MAGIC) {
        persistantData.rcc_reset_reason = 0;
        persistantData.reset_counter = 0;
        persistantData.reset_magic_before_reset = 0;
        persistantData.reset_magic_after_reset = 0;
        persistantData.magic = PERSISTANT_MAGIC;
    }
    // Clear the reset reason so we don't accidentally use it twice
    persistantData.reset_magic_after_reset = persistantData.reset_magic_before_reset;
    persistantData.reset_magic_before_reset = 0;

    // Check reset reason when we start.
    uint32_t reset_csr_flags = RCC->CSR;
    RCC->CSR |= RCC_CSR_RMVF; // Clear reset reasons
    if (reset_csr_flags & RCC_CSR_IWDGRSTF) {
        // Independent watchdog reset
        persistantData.rcc_reset_reason = DSG_ENUM_STARTUP_REASON_WATCHDOG_RESET;
    } else if (reset_csr_flags & RCC_CSR_PINRSTF) {
        // NRST pin reset
        persistantData.rcc_reset_reason = DSG_ENUM_STARTUP_REASON_PIN_RESET;
    } else if (reset_csr_flags & RCC_CSR_SFTRSTF) {
        // Software reset
        persistantData.rcc_reset_reason = DSG_ENUM_STARTUP_REASON_SOFTWARE_RESET;
    }
}

void loop() { jabus_mainloop_handler(); }