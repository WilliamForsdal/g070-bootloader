#pragma once
#include "stm32g0xx_ll_usart.h"


void uart_tx_blocking(uint8_t *data, int num_bytes);
int uart_tx(uint8_t *data, int num_bytes);