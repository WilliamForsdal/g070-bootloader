#include "systick.h"

// Interrupt handler
void systick_handler()
{
    persistantData.main_state.systick_counter++;
}
