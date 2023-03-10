#include "main.h"
#include "jabus.h"
#include "flashlowlevel/ll_flash.h"
#include "stm32g0xx_ll_gpio.h"
#include "stm32g0xx_ll_rcc.h"
#include "stm32g0xx_ll_usart.h"
#include "stm32g0xx_ll_utils.h"

#include "init.h"
#include "settings/settings.h"
#include "systick.h"

void cmd_handler_byte(uint8_t rx);
void check_startup_reason();
void loop();
void uart_tx_blocking(uint8_t byte);
void handle(uint8_t b);
void jabus_handler_mainloop();

extern uint8_t _bss_end[];
// extern uint8_t *__FLASH2_START__[0];

int uart_tx(uint8_t byte)
{
    if ((USART1->ISR & USART_ISR_TXE_TXFNF) == 0) {
        return 0;
    }
    USART1->TDR = byte;
    return 1;
}

void uart_tx_w(uint32_t word)
{
    uart_tx_blocking((word)&0xff);
    uart_tx_blocking((word >> 8) & 0xff);
    uart_tx_blocking((word >> 16) & 0xff);
    uart_tx_blocking((word >> 24) & 0xff);
}

// Returns -1 if nothing in buffer, else value.
int uart_rx()
{
    if (USART1->ISR & USART_ISR_RXNE_RXFNE) {
        return USART1->RDR;
    } else {
        return -1;
    }
}

// Call this to reset CPU from software
static inline void system_reset()
{
    __NVIC_SystemReset(); // This does not return.
}

void uart_tx_blocking(uint8_t byte)
{
    while (uart_tx(byte) == 0) {
    }
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
    uint32_t bruh = settings_new.settings1->setting2;

    // Initialize oscillator, timers and peripherals

    setup();
    if (bruh) {
        LED_ON();
    } else {
        LED_OFF();
    }
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
    uart_tx_w(settings_new.settings1->setting2);
}

void loop() {
    jabus_handler_mainloop();
}


void jabus_handler_mainloop() {
    if(js.got_pkt) {
        uart_tx(0xaa);
        uart_tx(0xaa);
        uart_tx(0xaa);
        uart_tx(0xaa);
        uart_tx(0xaa);
        uart_tx(0xaa);
        js.got_pkt = 0;
    }
}

void USART1_IRQHandler()
{
    if (USART1->ISR & USART_ISR_FE) {
        USART1->ICR |= USART_ICR_FECF;
    }

    if (USART1->ISR & USART_ISR_RXNE_RXFNE) {
        while (1) {
            int rx = uart_rx();
            if (rx >= 0) {
                // uart_tx(rx);
                handle(rx);
            } else {
                break;
            }
        }
    }
}
