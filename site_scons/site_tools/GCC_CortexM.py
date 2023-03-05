# GCC_ESP82xx

import os
import sys
import SCons.Action
import SCons.Builder
import SCons.Util

import util.GCC_adapter


def __find(env):
    paths = []
    for prg in ("C:/Program Files", "C:/Program Files (x86)"):
        for sub_dir in ("GNU Tools Arm Embedded", "GNU Arm Embedded Toolchain", "Arm GNU Toolchain arm-none-eabi"):
            gnu = os.path.join(prg, sub_dir)
            paths.append(gnu)
            if not os.path.exists(gnu):
                continue
            gnu = os.path.abspath(gnu)
            test = os.path.join(gnu, env["CC_VER"])
            if os.path.exists(test):
                return test

    print ("Couldn't find GCC version", env["CC_VER"])
    print ("Looked in")
    for p in paths:
        print (p)
    sys.exit(-1)


def exists(env):
  return __find(env)

def generate(env):
    """Add Builders and construction variables to the Environment."""

    env["ENV"]["PATH"] = __find(env)+"/bin"

    cc_prefix = "arm-none-eabi-"
    util.GCC_adapter.generate_helper(env, cc_prefix)

    cpu_man, cpu_mod, cpu_core = env["CPU"]

    env.Append(
        CPPPATH = ["."],     # always include root src directory in path
        CCFLAGS = [
            "-g",                   # Produce debugging information in the operating system’s native format
            "-mthumb",              # use thumb instruction set
            "-ffunction-sections",  # Place each function item into its own section in the output file if the target supports arbitrary sections.
            "-fdata-sections",      # Place each data item into its own section in the output file if the target supports arbitrary sections.
            "-Wall",                # warning for all
            "-Wextra",              # and extra warnings...
            "-Wa,-a,-adl=${TARGET.base}.lst",   # GCC: Generate list files with ASM
#                       "-nostdinc",            # Do not search the standard system directories for header files. Only the directories explicitly specified with -I, -iquote, -isystem, and/or -idirafter options (and the directory of the current file, if appropriate) are searched.
            "-Wpointer-arith",      # warning for dubious ptrs arithmetics
            # "-target armv7m-none-eabi",    # for clang!
        ],
        LINKFLAGS = [
            "-Wl,-no-keep-memory",
            "-mthumb",
            "-Wl,-cref",                # Output a cross reference table. If a linker map file is being generated, the cross reference table is printed to the map file
            "-Wl,--Map=${TARGET.base}.map,--cref",
            "-nostartfiles",        # Do not use the standard system startup files when linking. The standard system libraries are used normally, unless -nostdlib or -nodefaultlibs is used.
            "-nodefaultlibs",       # Do not use the standard system libraries when linking. Only the libraries you specify are passed to the linker, and options specifying linkage of the system libraries
            "-nostdlib",            # Do not use the standard system startup files or libraries when linking. No startup files and only the libraries you specify are passed to the linker,
        ],
        LIBS = [
            "c_nano",
            "gcc",
        ],
    )

    cpu_core_cflag_map = {
        "M0+" : "cortex-m0plus",
        "M3"  : "cortex-m3",
    }
    env.Append(CCFLAGS = [ "-mcpu="+cpu_core_cflag_map[cpu_core] ] )
    env.Append(LINKFLAGS = [ "-mcpu="+cpu_core_cflag_map[cpu_core] ] )

    env["PROGSUFFIX"] = ".elf"

