#include "main.h"
#include "fatal_error.h"
#include "flashlowlevel/ll_flash.h"
#include "init.h"
#include "jabus.h"
#include "settings/settings.h"
#include "stm32g0xx_ll_gpio.h"
#include "stm32g0xx_ll_rcc.h"
#include "stm32g0xx_ll_utils.h"
#include "systick.h"
#include "uart1.h"
#include "string.h"

struct PersistantDataSingleton SECTION_PERSISTANT_RAM persistantData;
struct LinkerSymbols linkerSymbols;

void save_startup_reason_copy_vars();
void check_startup_reason_and_reply();
void main_normal_mode();
void main_config_mode();

void HardFault_Handler()
{
    persistantData.main_state.state = DSG_ENUM_MAIN_STATE_HARDFAULT;
    BREAK;
    while (1) {
        LED_ON();
    }
}

int main(void)
{
    save_startup_reason_copy_vars();
    persistantData.main_state.state = DSG_ENUM_MAIN_STATE_STARTUP;

    // Init everything that is common to all modes.
    init_core();
    settings_init();
    // Check startup reason and jump to mode
    switch (persistantData.rcc_reset_reason) {
    case DSG_ENUM_STARTUP_REASON_WATCHDOG_RESET:
        fatal_error_no_ret(DSG_ENUM_FATAL_ERROR_CODE_WATCHDOG_RESET);
        // Never gets here
        return 0;

    case DSG_ENUM_STARTUP_REASON_COLD:
    case DSG_ENUM_STARTUP_REASON_PIN_RESET:
    default:
        // Initialize oscillator, systick, timers, and peripherals
        main_normal_mode();
        // Normal startup
        break;
    }

    // If request reset from external source, send reply.
    if (persistantData.reset_magic_after_sw_reset != 0) {
        js.buf->header.dst = 0;
        js.buf->header.length = sizeof(struct JabusAnswerReset);
        js.buf->header.cmd = JABUS_CMD_RESET;
        struct JabusAnswerReset *rst_cmd = &js.buf->cmds.ansReset;
        rst_cmd->current_mode_magic = persistantData.reset_magic_after_sw_reset;
        send_jabus_ans();
    }

    // We should never get here.
    while (1) {
    }
    return 0;
}

void main_normal_mode()
{
    persistantData.main_state.state = DSG_ENUM_MAIN_STATE_NORMAL_MODE;
    while (1) {
        mainloop_common();
    }
}

void main_config_mode() {
    
    persistantData.main_state.state = DSG_ENUM_MAIN_STATE_CONFIG_MODE;
    while (1) {
        mainloop_common();
    }
}

/// @brief Keep the linker vars in a struct at runtime so it's easier to use them.
void set_linker_symbols()
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
}

void save_startup_reason_copy_vars()
{
    set_linker_symbols();
    // If first start, reset_counter will be set when we check persistantData.magic.
    // If sw reset or other reset, this counter will increase.
    persistantData.reset_counter++;

#define PERSISTANT_MAGIC 0xb41e6ea0 // Just a random number.
    if (persistantData.magic != PERSISTANT_MAGIC) {
        uint32_t i;
        uint32_t *pdata = (uint32_t *)(&persistantData);
        for (i = 0; i < (sizeof(struct PersistantDataSingleton) / sizeof(uint32_t)); i++) {
            *pdata++ = 0;
        }
        persistantData.magic = PERSISTANT_MAGIC;
    } else {

        // Clear the reset reason so we don't accidentally use it twice
        persistantData.reset_magic_after_sw_reset = persistantData.reset_magic_before_sw_reset;
        persistantData.reset_magic_before_sw_reset = 0;

        // Save the previous mainstate so we can check it later.
        memcpy(&persistantData.main_state_before_last_reset, &persistantData.main_state, sizeof(persistantData.main_state));
    }

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
    else {
        persistantData.rcc_reset_reason = 0;
    }
}

// All modes must call this.
void mainloop_common()
{
    jabus_mainloop_handler();
    iwdg_kick();
}