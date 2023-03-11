#include "stm32g0xx_ll_gpio.h"


#define SECTION_RAMFUNC __attribute__((section(".RamFunc"), noinline))

#define IS_LED_ON()  ((GPIOA->ODR & LL_GPIO_PIN_5) == LL_GPIO_PIN_5)
#define IS_LED_OFF() ((GPIOA->ODR & LL_GPIO_PIN_5) != LL_GPIO_PIN_5)
#define LED_ON()     GPIOA->BSRR = LL_GPIO_PIN_5
#define LED_OFF()    GPIOA->BRR = LL_GPIO_PIN_5
