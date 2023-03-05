#include "systick.h"
#include "board.h"

volatile uint32_t systick_counter;

// Interrupt handler
void SysTick_Handler()
{
    systick_counter++;
}
