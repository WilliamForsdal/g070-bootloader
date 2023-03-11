#include "main.h"
#include "flashlowlevel/ll_flash.h"
#include "jabus.h"
#include "stm32g0xx_ll_gpio.h"
#include "stm32g0xx_ll_rcc.h"
#include "stm32g0xx_ll_utils.h"

#include "init.h"
#include "settings/settings.h"
#include "systick.h"

void check_startup_reason();
void loop();

extern uint8_t _bss_end[];
// extern uint8_t *__FLASH2_START__[0];

// Call this to reset CPU from software
static inline void system_reset()
{
    __NVIC_SystemReset(); // This does not return.
}

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
    check_startup_reason();
    settings_init();
    // uint32_t bruh = settings_new.settings1->setting2;

    // Initialize oscillator, timers and peripherals

    setup_normal_mode();
    // Main loop
    while (1) {
        loop();
    }
}

void check_startup_reason()
{
    // Check reset reason when we start.
    uint32_t reset_csr_flags = RCC->CSR;
    LL_RCC_ClearResetFlags(); // Clear reset reasons

    if (reset_csr_flags & RCC_CSR_IWDGRSTF) {
        // handle_iwdg_reset();
    }
}

/// @brief
void test_settings()
{
    settings_copy_to_union(SETTINGS_MAIN_BLOCK_IDX_SETTINGS1);
    settings_union_data.settings1.setting2 = !settings_union_data.settings1.setting2;
    if (settings_union_data.settings1.setting2) {
        LED_ON();
    } else {
        LED_OFF();
    }
    settings_union_data.settings1.crc32 = settings_calc_crc(SETTINGS_MAIN_BLOCK_IDX_SETTINGS1, &settings_union_data);
    settings_write_block(SETTINGS_MAIN_BLOCK_IDX_SETTINGS1, &settings_union_data);
}

void loop() { jabus_mainloop_handler(); }