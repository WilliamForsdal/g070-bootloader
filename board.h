#include "stm32g0xx_hal_gpio.h"

#define LED_ON() GPIOA->BSRR = GPIO_PIN_5
#define LED_OFF() GPIOA->BRR = GPIO_PIN_5
