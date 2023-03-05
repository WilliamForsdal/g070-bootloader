
#include "stm32g0xx.h"
#include "stm32g0xx_ll_rcc.h"
#include "stm32g0xx_ll_gpio.h"
#include "stm32g0xx_ll_utils.h"

#include "main.h"
#include "init.h"
#include "systick.h"
#include "board.h"

void check_startup_reason();
void loop();

extern uint8_t _bss_end[];
// extern uint8_t *__FLASH2_START__[0];

// Call this to reset CPU from software
static inline void system_reset()
{
    __NVIC_SystemReset(); // This does not return.
}

void uart_tx(uint8_t byte)
{
    while ((USART1->ISR & USART_ISR_TXE_TXFNF) == 0)
    {
    }
    USART1->TDR = byte;
}

int uart_rx()
{
    // Returns -1 if nothing in buffer, else value.
    if (USART1->ISR & USART_ISR_RXNE_RXFNE)
    {
        return USART1->RDR;
    }
    else
    {
        return -1;
    }
}

int main(void)
{
    check_startup_reason();

    // Initialize oscillator, timers and peripherals
    setup();

    // uint32_t bss_e = (uint32_t)_bss_end;
    // uart_tx((bss_e)&0xff);
    // uart_tx((bss_e >> 8) & 0xff);
    // uart_tx((bss_e >> 16) & 0xff);
    // uart_tx((bss_e >> 24) & 0xff);

    // Main loop
    while (1)
    {
        loop();
    }
}

void check_startup_reason()
{
    // Check reset reason when we start.
    uint32_t reset_csr_flags = RCC->CSR;
    LL_RCC_ClearResetFlags(); // Clear reset reasons

    if (reset_csr_flags & RCC_CSR_IWDGRSTF)
    {
        // handle_iwdg_reset();
    }
}

void loop()
{
    static uint32_t shiet = 0;

    int rx = uart_rx();
    // uart_tx(_bss_end & 0xff);
    // uart_tx((__FLASH2_START__>>) & 0xff);
    if (rx >= 0)
    {
        uart_tx(rx);
        uart_tx(rx + 1);
        uart_tx(rx + 2);
        uart_tx(rx + 3);
        if (shiet)
        {
            LED_OFF();
            shiet = 0;
        }
        else
        {
            LED_ON();
            shiet = 1;
        }
    }
}
