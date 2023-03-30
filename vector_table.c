/**
 * Defines the vector table and weak aliases for all handlers.
 */

#include <stdint.h>
#ifndef BREAK
#define BREAK __asm__("BKPT")
#endif

struct VectorTable {
    uint32_t stackpointer;
    void (*reset_handler)(void);
    void (*nmi_handler)(void);
    void (*hardfault_handler)(void);
    uint32_t _pad_04;
    uint32_t _pad_05;
    uint32_t _pad_06;
    uint32_t _pad_07;
    uint32_t _pad_08;
    uint32_t _pad_09;
    uint32_t _pad_10;
    void (*svc_handler)(void);
    uint32_t _pad_12;
    uint32_t _pad_13;
    void (*pend_sv_handler)(void);
    void (*systick_handler)(void);
    void (*wwdg_handler)(void);
    uint32_t _pad_17;
    void (*rtc_tamp_handler)(void);
    void (*flash_handler)(void);
    void (*rcc_handler)(void);
    void (*exti_0_1_handler)(void);
    void (*exti_2_3_handler)(void);
    void (*exti_4_15_handler)(void);
    uint32_t _pad_24;
    void (*dma1_ch_1_handler)(void);
    void (*dma1_ch_2_3_handler)(void);
    void (*dma1_ch_4_7_mux_ovr_handler)(void);
    void (*adc1_handler)(void);
    void (*tim1_brk_up_trg_com_handler)(void);
    void (*tim1_cc_handler)(void);
    uint32_t _pad_31;
    void (*tim3_handler)(void);
    void (*tim6_handler)(void);
    void (*tim7_handler)(void);
    void (*tim14_handler)(void);
    void (*tim15_handler)(void);
    void (*tim16_handler)(void);
    void (*tim17_handler)(void);
    void (*i2c1_handler)(void);
    void (*i2c2_handler)(void);
    void (*spi1_handler)(void);
    void (*spi2_handler)(void);
    void (*usart1_handler)(void);
    void (*usart2_handler)(void);
    void (*usart_3_4_handler)(void);
};

extern const uint8_t _estack[];
extern const uint8_t _sdata[];
extern const uint8_t _edata[];

void default_handler()
{
    BREAK;
    while (1) {
    }
}

// Defined in _startup.s
extern void Reset_Handler();

// Defines a weak alias for the default handler function
#define WEAK_ALIAS_HANDLER_DEFAULT(func) void func() __attribute__((weak, alias("default_handler")))

// Weak aliases for these functions. 
WEAK_ALIAS_HANDLER_DEFAULT(nmi_handler);
WEAK_ALIAS_HANDLER_DEFAULT(hardfault_handler);
WEAK_ALIAS_HANDLER_DEFAULT(svc_handler);
WEAK_ALIAS_HANDLER_DEFAULT(pend_sv_handler);
WEAK_ALIAS_HANDLER_DEFAULT(systick_handler);
WEAK_ALIAS_HANDLER_DEFAULT(wwdg_handler);
WEAK_ALIAS_HANDLER_DEFAULT(rtc_tamp_handler);
WEAK_ALIAS_HANDLER_DEFAULT(flash_handler);
WEAK_ALIAS_HANDLER_DEFAULT(rcc_handler);
WEAK_ALIAS_HANDLER_DEFAULT(exti_0_1_handler);
WEAK_ALIAS_HANDLER_DEFAULT(exti_2_3_handler);
WEAK_ALIAS_HANDLER_DEFAULT(exti_4_15_handler);
WEAK_ALIAS_HANDLER_DEFAULT(dma1_ch_1_handler);
WEAK_ALIAS_HANDLER_DEFAULT(dma1_ch_2_3_handler);
WEAK_ALIAS_HANDLER_DEFAULT(dma1_ch_4_7_mux_ovr_handler);
WEAK_ALIAS_HANDLER_DEFAULT(adc1_handler);
WEAK_ALIAS_HANDLER_DEFAULT(tim1_brk_up_trg_com_handler);
WEAK_ALIAS_HANDLER_DEFAULT(tim1_cc_handler);
WEAK_ALIAS_HANDLER_DEFAULT(tim3_handler);
WEAK_ALIAS_HANDLER_DEFAULT(tim6_handler);
WEAK_ALIAS_HANDLER_DEFAULT(tim7_handler);
WEAK_ALIAS_HANDLER_DEFAULT(tim14_handler);
WEAK_ALIAS_HANDLER_DEFAULT(tim15_handler);
WEAK_ALIAS_HANDLER_DEFAULT(tim16_handler);
WEAK_ALIAS_HANDLER_DEFAULT(tim17_handler);
WEAK_ALIAS_HANDLER_DEFAULT(i2c1_handler);
WEAK_ALIAS_HANDLER_DEFAULT(i2c2_handler);
WEAK_ALIAS_HANDLER_DEFAULT(spi1_handler);
WEAK_ALIAS_HANDLER_DEFAULT(spi2_handler);
WEAK_ALIAS_HANDLER_DEFAULT(usart1_handler);
WEAK_ALIAS_HANDLER_DEFAULT(usart2_handler);
WEAK_ALIAS_HANDLER_DEFAULT(usart_3_4_handler);

#define SECTION_ISR_VECTOR __attribute__((section(".isr_vector")))

// Vector table at 0x08000000:
volatile const struct VectorTable SECTION_ISR_VECTOR vector_table = {
    .stackpointer = (uint32_t)_estack,
    .reset_handler = Reset_Handler,
    .nmi_handler = nmi_handler,
    .hardfault_handler = hardfault_handler,
    .svc_handler = svc_handler,
    .pend_sv_handler = pend_sv_handler,
    .systick_handler = systick_handler,
    .wwdg_handler = wwdg_handler,
    .rtc_tamp_handler = rtc_tamp_handler,
    .flash_handler = flash_handler,
    .rcc_handler = rcc_handler,
    .exti_0_1_handler = exti_0_1_handler,
    .exti_2_3_handler = exti_2_3_handler,
    .exti_4_15_handler = exti_4_15_handler,
    .dma1_ch_1_handler = dma1_ch_1_handler,
    .dma1_ch_2_3_handler = dma1_ch_2_3_handler,
    .dma1_ch_4_7_mux_ovr_handler = dma1_ch_4_7_mux_ovr_handler,
    .adc1_handler = adc1_handler,
    .tim1_brk_up_trg_com_handler = tim1_brk_up_trg_com_handler,
    .tim1_cc_handler = tim1_cc_handler,
    .tim3_handler = tim3_handler,
    .tim6_handler = tim6_handler,
    .tim7_handler = tim7_handler,
    .tim14_handler = tim14_handler,
    .tim15_handler = tim15_handler,
    .tim16_handler = tim16_handler,
    .tim17_handler = tim17_handler,
    .i2c1_handler = i2c1_handler,
    .i2c2_handler = i2c2_handler,
    .spi1_handler = spi1_handler,
    .spi2_handler = spi2_handler,
    .usart1_handler = usart1_handler,
    .usart2_handler = usart2_handler,
    .usart_3_4_handler = usart_3_4_handler,
};