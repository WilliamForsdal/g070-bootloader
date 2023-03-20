#pragma once
#include "stm32g0xx_ll_usart.h"

int uart_rx();
int uart_tx(uint8_t byte);
void uart_tx_w(uint32_t word);
void uart_tx_blocking(uint8_t byte);
