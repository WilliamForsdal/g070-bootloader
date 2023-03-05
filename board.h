#include "stm32g0xx_ll_gpio.h"

#define LED_ON() GPIOA->BSRR = LL_GPIO_PIN_5
#define LED_OFF() GPIOA->BRR = LL_GPIO_PIN_5
