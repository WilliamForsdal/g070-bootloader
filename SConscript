Import( "env" )
import os
import string


srcs = [
    "_startup.s",
    "main.c",
    "init.c",
    "systick.c",
    "settings/settings.c",
    "_main.c",
    "sw_crc.c",
    # "dbg_print.c"
    # "stm32g0xx_hal_msp.c",
    # "stm32g0xx_it.c",
    # "syscalls.c",
    # "sysmem.c",
    # "system_stm32g0xx.c",
]

srcs += [
    "flashlowlevel/ll_flash.c",
    "flashlowlevel/drv_st/ll_flash_stm32g0.c",
]
srcs += [
    "JabusStack/jabus_handler.c",
    "JabusStack/cmd_handlers.c",
]

srcs += [
    # "Drivers/STM32G0xx_HAL_Driver/Src/stm32g0xx_hal.c",  
    # "Drivers/STM32G0xx_HAL_Driver/Src/stm32g0xx_hal_cortex.c",   
    # "Drivers/STM32G0xx_HAL_Driver/Src/stm32g0xx_hal_dma.c",  
    # "Drivers/STM32G0xx_HAL_Driver/Src/stm32g0xx_hal_dma_ex.c",   
    # "Drivers/STM32G0xx_HAL_Driver/Src/stm32g0xx_hal_exti.c", 
    # "Drivers/STM32G0xx_HAL_Driver/Src/stm32g0xx_hal_flash.c",    
    # "Drivers/STM32G0xx_HAL_Driver/Src/stm32g0xx_hal_flash_ex.c", 
    # "Drivers/STM32G0xx_HAL_Driver/Src/stm32g0xx_hal_gpio.c", 
    # "Drivers/STM32G0xx_HAL_Driver/Src/stm32g0xx_hal_pwr.c",  
    # "Drivers/STM32G0xx_HAL_Driver/Src/stm32g0xx_hal_pwr_ex.c",   
    # "Drivers/STM32G0xx_HAL_Driver/Src/stm32g0xx_hal_rcc.c",  
    # "Drivers/STM32G0xx_HAL_Driver/Src/stm32g0xx_hal_rcc_ex.c",   
    # # "Drivers/STM32G0xx_HAL_Driver/Src/stm32g0xx_hal_tim.c",  
    # # "Drivers/STM32G0xx_HAL_Driver/Src/stm32g0xx_hal_tim_ex.c",   
    # "Drivers/STM32G0xx_HAL_Driver/Src/stm32g0xx_hal_uart.c", 
    # "Drivers/STM32G0xx_HAL_Driver/Src/stm32g0xx_hal_uart_ex.c",  
    # "Drivers/STM32G0xx_HAL_Driver/Src/stm32g0xx_ll_dma.c",   
    # "Drivers/STM32G0xx_HAL_Driver/Src/stm32g0xx_ll_rcc.c",   
]

bin = env.Program("bin", srcs)
env.SFile(bin)

# compile and link ish:
# arm-none-eabi-gcc main.c .\startup.s -mcpu=cortex-m0plus -T"linkscript.ld" --specs=nosys.specs -o build/a.out
# .mot file:
# arm-none-eabi-objcopy.exe .\build\a -O srec .\build\b.mota