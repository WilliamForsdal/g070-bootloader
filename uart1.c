
#include "uart1.h"
#include "board.h"
extern void uart_rx_handler(uint8_t b);

int uart_tx(uint8_t byte)
{
    if ((USART1->ISR & USART_ISR_TXE_TXFNF) == 0) {
        return -1;
    }
    USART1->TDR = byte;
    return 0;
}

void uart_tx_blocking(uint8_t byte)
{
    while (!uart_tx(byte)) {
    }
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

void USART1_IRQHandler()
{
    if (USART1->ISR & USART_ISR_FE) {
        USART1->ICR |= USART_ICR_FECF;
    }
    while (USART1->ISR & USART_ISR_RXNE_RXFNE) {
        uint8_t rx = (uint8_t)(USART1->RDR & 0xff);
        uart_rx_handler(rx);
    }
}
