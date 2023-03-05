#include "init.h"
#include "stm32g0xx.h"
#include "stm32g0xx_ll_rcc.h"
#include "stm32g0xx_ll_gpio.h"
#include "stm32g0xx_ll_usart.h"
#include "systick.h"

static inline void gpio_cfg_af(GPIO_TypeDef *port, uint16_t pin, uint32_t alternate_func, uint32_t speed)
{
    LL_GPIO_SetPinMode(port, pin, LL_GPIO_MODE_ALTERNATE);
    LL_GPIO_SetPinSpeed(port, pin, speed);
    LL_GPIO_SetAFPin_0_7(port, pin, alternate_func);
}

static inline void gpio_cfg(GPIO_TypeDef *port, uint16_t pin, uint32_t mode, uint32_t speed)
{
    LL_GPIO_SetPinMode(port, pin, mode);
    LL_GPIO_SetPinSpeed(port, pin, speed);
}

void init_gpio()
{
    RCC->IOPENR |= RCC_IOPENR_GPIOAEN; // enable clock for GPIOA
    __NOP(); // Delay after an RCC peripheral clock enabling
    __NOP();
    __NOP();
    RCC->IOPENR |= RCC_IOPENR_GPIOCEN; 
    gpio_cfg(GPIOA, LL_GPIO_PIN_5, LL_GPIO_MODE_OUTPUT, LL_GPIO_SPEED_FREQ_HIGH);

    // alternate function (USART1)
    gpio_cfg_af(GPIOC, LL_GPIO_PIN_4, LL_GPIO_AF_1, LL_GPIO_SPEED_FREQ_LOW);
    gpio_cfg_af(GPIOC, LL_GPIO_PIN_5, LL_GPIO_AF_1, LL_GPIO_SPEED_FREQ_LOW);
}

static inline void init_systick()
{
    SysTick->LOAD = (uint32_t)(SYSTICK_TICKS_PER_1KHZ);
    NVIC_SetPriority(SysTick_IRQn, (1UL << __NVIC_PRIO_BITS) - 1UL);
    SysTick->VAL = 0UL;
    SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk |
                    SysTick_CTRL_TICKINT_Msk |
                    SysTick_CTRL_ENABLE_Msk;
}

static inline void init_usart(USART_TypeDef *uart)
{
    RCC->APBENR2 |= (uint32_t)(1 << 14); // Enable uart1 clock
    __NOP(); // Delay after an RCC peripheral clock enabling
    __NOP();
    __NOP();

    LL_USART_ConfigAsyncMode(uart);

    // Configure baudrate
    // USARTDIV 
    uart->BRR = (CLOCK_SPEED / 115200);
    SET_BIT(uart->CR1, USART_CR1_UE);
    SET_BIT(uart->CR1, USART_CR1_TE);
    SET_BIT(uart->CR1, USART_CR1_RE);
}

int setup()
{
    // Enable prefetch buffer
    SET_BIT(FLASH->ACR, FLASH_ACR_PRFTEN);

    init_gpio();
    init_systick();
    init_usart(USART1);

    return 0;
}