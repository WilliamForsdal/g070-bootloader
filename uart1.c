
#include "uart1.h"
#include "board.h"
#include "iwdg.h"
#define UART_TX_RINGBUF_SIZE 256 // Make sure this is a multiple of 2 so we avoid expensive division.
struct UartTxRingBuffer {
    uint16_t head;
    uint16_t tail;
    uint8_t buf[UART_TX_RINGBUF_SIZE];
};
struct UartTxRingBuffer tx_buf;

extern void uart_rx_handler(uint8_t b);

#define DISABLE_TX_IRQ() (USART1->CR1 &= ~USART_CR1_TXFEIE)
#define ENABLE_TX_IRQ()  (USART1->CR1 |= USART_CR1_TXFEIE)

int uart_tx_free() { return UART_TX_RINGBUF_SIZE - 1 - (tx_buf.head - tx_buf.tail); }
static inline int uart_tx_current_bytes() { return tx_buf.head - tx_buf.tail; }

// This pushes as many bytes as possible to hw, and then enables txfifo empty irq.
static inline void uart_push_data_from_ringbuf_to_hw()
{
    // USART1->CR1 &= ~USART_CR1_TXFEIE; // Disable usart irq during tail update
    DISABLE_TX_IRQ();
    if (tx_buf.tail == tx_buf.head) {
        return;
    }
    while ((tx_buf.tail != tx_buf.head) && (USART1->ISR & USART_ISR_TXE_TXFNF)) {
        USART1->TDR = tx_buf.buf[tx_buf.tail];
        tx_buf.tail = (tx_buf.tail + 1) % UART_TX_RINGBUF_SIZE;
    }
    if (tx_buf.tail != tx_buf.head) {
        // USART1->CR1 |= USART_CR1_TXFEIE; // Reenable irq, more data to send but hw buf full.
        ENABLE_TX_IRQ(); // More to send, wait for fifo to have room for more data
    }
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

/// @brief Push data to uart ringbuf, and start tx. Can be called from userspace.
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
    uart_push_data_from_ringbuf_to_hw();
    return handled;
}

void USART1_IRQHandler()
{
    if (USART1->ISR & (USART_ISR_TXFE) && (USART1->CR1 & USART_CR1_TXFEIE)) {
        int num_to_tx = uart_tx_current_bytes();
        if (num_to_tx == 0) {
            DISABLE_TX_IRQ();
        } else {
            // Transmit buffer empty and we have more data to send:
            //   Push data from ringbuffer if available
            //   clear irq flag
            uart_push_data_from_ringbuf_to_hw();
            // USART1->ICR |= (USART_ICR_TCCF | USART_ICR_TXFECF); 
        }
    }
    while (USART1->ISR & USART_ISR_RXNE_RXFNE) {
        uint8_t rx = (uint8_t)(USART1->RDR & 0xff);
        uart_rx_handler(rx);
    }
}
