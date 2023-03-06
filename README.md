# NUCLEO-G070RB Bootloader
Test bootloader for G070RB

## Debugging

1. Install Cortex-M debug
2. Download https://github.com/stlink-org/stlink/releases/tag/v1.7.0
3. In .vscode/settings.json, add GDB and st-util paths:
```
    "cortex-debug.gdbPath": "C:/Program Files (x86)/Arm GNU Toolchain arm-none-eabi/12.2 mpacbti-bet1/bin/arm-none-eabi-gdb.exe",
    "cortex-debug.stutilPath": "C:/bin/stlink-1.7.0-i686-w64-mingw32/bin/st-util.exe",
```
4. Add the debug configuration:
```
{
    "name": "Flash & Debug",
    "cwd": "${workspaceRoot}",
    "executable": "${workspaceRoot}/build/bin.elf",
    "type": "cortex-debug",
    "request": "launch",
    // "preLaunchCommands": ["scons"],
    "servertype": "stutil",
    "device": "STM32G070RB",
    "interface": "swd",
    "showDevDebugOutput": "raw",
    "runToMain": true
}
```