# used by most GCC based builders. Probably also CLang builders.
import os
import SCons.Action
import SCons.Builder
import SCons.Util

def generate_helper(env, cc_prefix):
    gnu_tools = ['gcc', 'g++', 'gnulink', 'ar', 'gas']
    for tool in gnu_tools:
        SCons.Tool.Tool(tool)(env)

    env["CC"] = cc_prefix + "gcc"
    env["CXX"] = cc_prefix + "g++"
    env["AS"] = cc_prefix + "as"
    env["OBJCOPY"] = cc_prefix + "objcopy"
    env["OBJDUMP"] = cc_prefix + "objdump"
    env["SIZE"] = cc_prefix + "size"

    objcopyActionsSRec = [
#        "arm-none-eabi-objcopy%s -R .boot_persistant_data -R .boot_bss -R .2bss -O srec $SOURCE $TARGET" % EXE_ENDING,
        "$OBJCOPY -R .boot_persistant_data -R .boot_bss -R .2bss -O srec $SOURCE $TARGET",
        "$OBJDUMP -x --wide --disassemble -l $SOURCE > ${TARGET}.objdump",
        "$SIZE $SOURCE",
    ]
    bldSFile = env.Builder(action = objcopyActionsSRec,
                           suffix = ".srec",
                           src_builder = env["BUILDERS"]["Program"],
                           src_suffix = ".elf"
                          )
    env["BUILDERS"]["SFile"] = bldSFile
