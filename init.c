#include "init.h"
#include "stm32g0xx.h"
#include "stm32g0xx_ll_gpio.h"
#include "stm32g0xx_ll_rcc.h"
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

static void init_clocks()
{
    RCC->IOPENR |= RCC_IOPENR_GPIOAEN; // enable clocks
    RCC->IOPENR |= RCC_IOPENR_GPIOBEN;
    RCC->IOPENR |= RCC_IOPENR_GPIOCEN;
    // RCC->IOPENR |= RCC_IOPENR_GPIODEN;
    RCC->APBENR2 |= (uint32_t)(1 << 14); // Enable uart1 clock
    __NOP();                             // Delay after an RCC peripheral clock enabling
    __NOP();
}

static void init_gpio()
{
    // LED
    gpio_cfg(GPIOA, LL_GPIO_PIN_5, LL_GPIO_MODE_OUTPUT, LL_GPIO_SPEED_FREQ_HIGH);

    // alternate function (USART1)
    gpio_cfg_af(GPIOC, LL_GPIO_PIN_4, LL_GPIO_AF_1, LL_GPIO_SPEED_FREQ_LOW);
    gpio_cfg_af(GPIOC, LL_GPIO_PIN_5, LL_GPIO_AF_1, LL_GPIO_SPEED_FREQ_LOW);
}

static void init_usart(USART_TypeDef *uart, int irq)
{
    // Usart fifos are 8-bytes deep.
    // Configure baudrate, oversampling=16:
    uart->BRR = (CLOCK_SPEED / 115200);
    uart->CR1 = USART_CR1_FIFOEN | USART_CR1_TE | USART_CR1_RE | USART_CR1_UE | USART_CR1_RXNEIE_RXFNEIE; //
    uart->CR3 = 0;

    if (irq) {
        NVIC_SetPriority(USART1_IRQn, (1UL << __NVIC_PRIO_BITS) - 1UL);
        NVIC_EnableIRQ(USART1_IRQn);
    }
}

int setup_normal_mode()
{
    // Enable prefetch buffer
    SET_BIT(FLASH->ACR, FLASH_ACR_PRFTEN);
    init_clocks();
    init_gpio();
    systick_init();
    init_usart(USART1, 1);
    return 0;
}
int setup_bootloader()
{
    // Enable prefetch buffer
    SET_BIT(FLASH->ACR, FLASH_ACR_PRFTEN);
    init_clocks();
    init_gpio();
    systick_init();
    init_usart(USART1, 0); // No irq.
    return 0;
}