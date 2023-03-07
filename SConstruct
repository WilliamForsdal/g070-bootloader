import os
import string

# -----------------------------------------------------------------------------

# speeds up things considerably on windows.
DefaultEnvironment(tools=[])

#CPU                = "GD32F105VC"
CPU_ARCH = "cortex-m0plus"
STACK_SIZE = "0x400"

cpu_tuple = ("ST", "STM32G070RB", "M0+")

env = Environment(
    tools=[
        Tool("gcc_cortexM"),
    ],
    CC_VER = "12.2 mpacbti-bet1",
    # CC_VER="10 2020-q4-major",
    CPU=cpu_tuple,
    VERBOSE=True,
)

# use Append(). If set in environment creation, then they completely override the flags in the build tool.
env.Append(
    CCFLAGS=[
        "-fdiagnostics-color=always",
        "-O0",
        "-g3",
        "-mcpu=%s" % CPU_ARCH,
        "-DSTM32G070xx",
        # "-DUSE_HAL_DRIVER",
    ],
    CXXFLAGS=[ # copied from 021-bigcpu
        "-std=c++11",
        "-fno-rtti",
        "-fno-exceptions",
        "-fno-non-call-exceptions",
        "-fno-use-cxa-atexit",
        "-ffreestanding",
        "-fno-common",
        "-ffunction-sections",
        "-fdata-sections",
    ],
    CFLAGS=[
        "-std=gnu11",
        # "-g", # ?
        #"-fdump-tree-cfg", "-fdump-tree-cfg-lineno",
        # "-finstrument-functions",
        # "-finstrument-functions-exclude-file-list=" + no_intrument_files(),
    ],
    LINKFLAGS=[
        "-Tlinkscript.ld",
        "-Wl,--gc-sections",
    ],
    ASFLAGS=[
        "-mcpu=%s" % CPU_ARCH,
    ],
    CPPPATH=[
        ".",
        "Drivers/CMSIS/include",
        "Drivers/CMSIS/device/include",
        "Drivers/CMSIS/Device/ST/STM32G0xx/Include/",
        "Drivers/STM32G0xx_HAL_Driver/Inc",
    ],
)

env.Append(PRODUCT_FAMILY=0, BUILD_DIR="build", CCFLAGS=[], CFLAGS=["-g",], LINKFLAGS=[])

SConscript("SConscript",
           variant_dir=env["BUILD_DIR"],
           duplicate=0,
           exports={"env": env},
           )
