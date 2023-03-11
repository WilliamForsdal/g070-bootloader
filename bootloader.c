#include "bootloader.h"
#include "systick.h"
void SECTION_RAMFUNC bootloader()
{
    // Boot only uses systick for time.
    
    while (1) {
        LED_ON();
    }
}