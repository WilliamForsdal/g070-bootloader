#include "systick.h"

// Interrupt handler
void SysTick_Handler()
{
    persistantData.main_state.systick_counter++;
}
