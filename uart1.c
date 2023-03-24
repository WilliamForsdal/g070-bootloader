
#include "uart1.h"
#include "iwdg.h"
#include "board.h"

#define UART_TX_RINGBUF_SIZE 256 // Make sure this is a multiple of 2 so we avoid expensive division.

struct UartTxRingBuffer {
    uint16_t head;
    uint16_t tail;
    uint8_t buf[UART_TX_RINGBUF_SIZE];
};
struct UartTxRingBuffer tx_buf;

extern void uart_rx_handler(uint8_t b);

static inline void uart_push_data_from_ringbuf_to_periph()
{
    USART1->CR1 &= ~USART_CR1_TXFEIE; // Disable usart irq during tail update
    while ((tx_buf.tail != tx_buf.head) && (USART1->ISR & USART_ISR_TXE_TXFNF)) {
        USART1->TDR = tx_buf.buf[tx_buf.tail];
        tx_buf.tail = (tx_buf.tail + 1) % UART_TX_RINGBUF_SIZE;
    }
    USART1->CR1 |= USART_CR1_TXFEIE; // Reenable irq
}

void uart_tx_blocking(uint8_t *data, int num_bytes)
{
    while (num_bytes) {
        int handled = uart_tx(data, num_bytes);
        data += handled;
        num_bytes -= handled;
        iwdg_kick();
    }
}

/// @brief Push data to uart ringbuf, and start tx.
/// @param data the data
/// @param bytes how many bytes.
/// @return how many bytes we handled. Caller should check this.
int uart_tx(uint8_t *data, int num_bytes)
{
    int handled = 0;
    while (num_bytes--) {
        uint16_t new_head = (tx_buf.head + 1) % UART_TX_RINGBUF_SIZE;
        if (new_head == tx_buf.tail) {
            break;
        }
        tx_buf.buf[tx_buf.head] = *data++;
        tx_buf.head = new_head;
        handled++;
    }
    uart_push_data_from_ringbuf_to_periph();
    return handled;
}

void USART1_IRQHandler()
{
    if (USART1->ISR & USART_ISR_FE) {
        USART1->ICR |= USART_ICR_FECF;
    }
    if (USART1->ISR & USART_ISR_TXFE) {
        // Transmit buffer empty:
        //   Push data from ringbuffer if available
        //   clear irq flag
        uart_push_data_from_ringbuf_to_periph();
        USART1->ICR |= USART_ICR_TXFECF; // Clear irq flag
    }
    while (USART1->ISR & USART_ISR_RXNE_RXFNE) {
        uint8_t rx = (uint8_t)(USART1->RDR & 0xff);
        uart_rx_handler(rx);
    }
}
