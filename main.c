#include "stm32g0xx.h"
#include "stm32g0xx_ll_rcc.h"
#include "stm32g0xx_ll_gpio.h"
#include "stm32g0xx_ll_utils.h"

#include "main.h"
#include "init.h"
#include "systick.h"
#include "board.h"
#include "flasher.h"
#include "settings/settings.h"

void cmd_handler_byte(uint8_t rx);
void check_startup_reason();
void loop();
void uart_tx_blocking(uint8_t byte);

extern uint8_t _flash2[];
extern uint8_t _bss_end[];
// extern uint8_t *__FLASH2_START__[0];

int uart_tx(uint8_t byte)
{
    if ((USART1->ISR & USART_ISR_TXE_TXFNF) == 0)
    {
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

// Call this to reset CPU from software
static inline void system_reset()
{
    __NVIC_SystemReset(); // This does not return.
}

void uart_tx_blocking(uint8_t byte)
{
    while (uart_tx(byte) == 0)
    {
    }
}

int main(void)
{
    check_startup_reason();

    // Initialize oscillator, timers and peripherals
    setup();
    settings_init();

    settings_copy_to_union(SETTINGS_MAIN_BLOCK_IDX_SETTINGS1);
    settings_union_data.settings1.setting2 = 0xB00B1E55;
    settings_union_data.settings1.crc32 = settings_calc_crc(SETTINGS_MAIN_BLOCK_IDX_SETTINGS1, &settings_union_data);
    uart_tx_w(settings_new.settings1->setting2);
    int ret = settings_write_block(SETTINGS_MAIN_BLOCK_IDX_SETTINGS1, &settings_union_data);
    uart_tx(ret);
    uart_tx_w(settings_new.settings1->setting2);

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

// static int shiet = 0;
void loop()
{
    // int rx = uart_rx();
    // uart_tx(_bss_end & 0xff);
    // uart_tx((__FLASH2_START__>>) & 0xff);
    // if (rx >= 0)
    // {
    //     // uart_tx(rx);

    //     uint32_t cnt = systick_counter;
    //     uart_tx((cnt >> 0) & 0xff);
    //     uart_tx((cnt >> 8) & 0xff);
    //     uart_tx((cnt >> 16) & 0xff);
    //     uart_tx((cnt >> 24) & 0xff);

    // }
}

void USART1_IRQHandler()
{

    if (USART1->ISR & USART_ISR_RXNE_RXFNE)
    {
        while (1)
        {
            int rx = uart_rx();
            if (rx >= 0)
            {
                // my_ram_func(rx);
                cmd_handler_byte(rx);
            }
            else
                break;
        }
    }
}

#define CMD_MAX_RX_LEN 1024
struct CmdState
{
    int num_rxed;
    int state;
    uint16_t rx_len; // How many bytes we expect.
    uint8_t buf[CMD_MAX_RX_LEN];
    int buf_ptr;
};

static struct CmdState state;

void cmd_handler_byte(uint8_t rx)
{

    state.num_rxed++;

    switch (state.state)
    {
    case 0: // Wait for preamble
        if (rx == 0xFF)
        {
            state.state++;
        }
        break;
    case 1: // Consume preambles
        if (rx != 0xFF)
        {
            state.state++;
            state.rx_len = rx; // lower 8 bits rxed.
        }
        break;

    case 2:
        state.rx_len |= (rx << 8); // got upper length byte

        if (state.rx_len > CMD_MAX_RX_LEN)
        {
            state.state = 0; // too large!
        }
        else
        {
            state.state++;
        }
        break;

    case 3:
        state.buf[state.buf_ptr++] = rx;
        if (state.buf_ptr == state.rx_len)
        {
            int i;
            for (i = 0; i < state.buf_ptr; i++)
            {
                uart_tx(state.buf[i]);
            }
            state.state = 0;
        }
        break;

    default:
        state.state = 0; // Go back to wait for preambles.
        break;
    }
}