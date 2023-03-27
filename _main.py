# auto generated
import struct
import ctypes
from typing import Tuple
import dataclasses
# constants


# Enum FATAL_ERROR_CODE(u32)
class ENUM_FATAL_ERROR_CODE:
    NO_ERROR                       = 0
    WATCHDOG_RESET                 = 1

# Enum JABUS_CMD_HANDLER_RET(i32)
class ENUM_JABUS_CMD_HANDLER_RET:
    OK                             = 0
    NOK                            = -1
    NOK_EXTDATA_BAD_FCS            = -2
    NOT_IMPLEMENTED                = -100

# Enum MAIN_STATE(u32)
class ENUM_MAIN_STATE:
    NORMAL_MODE                    = 0
    CONFIG_MODE                    = 1
    FATAL_ERROR                    = 2
    STARTUP                        = 10
    HARDFAULT                      = 11

# Enum RESET_MODE(u32)
class ENUM_RESET_MODE:
    NORMAL_OP_MODE                 = 1303728842
    BOOTLOADER_MODE                = 3186851212

# Enum STARTUP_REASON(u16)
class ENUM_STARTUP_REASON:
    COLD                           = 0
    WATCHDOG_RESET                 = 1
    SOFTWARE_RESET                 = 2
    PIN_RESET                      = 3

# Bitdef PROBE_OP_FLAGS(u16)
class BITDEF_PROBE_OP_FLAGS:
    IN_SMALL_BOOTLOADER_BIT        = 0
    IN_SMALL_BOOTLOADER_MASK       = 0x00000001
    IN_BIG_BOOTLOADER_BIT          = 1
    IN_BIG_BOOTLOADER_MASK         = 0x00000002
    SETTINGS_WRITE_OK_BIT          = 2
    SETTINGS_WRITE_OK_MASK         = 0x00000004
    ROUTING_OK_BIT                 = 3
    ROUTING_OK_MASK                = 0x00000008
    NORMAL_OP_BIT                  = 4
    NORMAL_OP_MASK                 = 0x00000010
    FATAL_ERROR_BIT                = 5
    FATAL_ERROR_MASK               = 0x00000020
    HALF_DUPLEX_BIT                = 6
    HALF_DUPLEX_MASK               = 0x00000040
    RESTART_NEEDS_FF_BIT           = 7
    RESTART_NEEDS_FF_MASK          = 0x00000080
    FLOW_CTRL_BIT                  = 8
    FLOW_CTRL_MASK                 = 0x00000100

# SerialNumbers
@dataclasses.dataclass
class Setting_SerialNumbers:
    SIZE = 68
    BIT_OFFSETS = {
        'serialNumbers' : 0, #u32
        'crc32' : 512, #u32
     }
    BYTE_OFFSETS = {
        'serialNumbers' : 0, #u32
        'crc32' : 64, #u32
     }
    serialNumbers: Tuple[int] = (0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,)
    crc32: int = 0
    def pack(self) -> bytes:
        return (b''
            + struct.pack("<L", self.serialNumbers[0])
            + struct.pack("<L", self.serialNumbers[1])
            + struct.pack("<L", self.serialNumbers[2])
            + struct.pack("<L", self.serialNumbers[3])
            + struct.pack("<L", self.serialNumbers[4])
            + struct.pack("<L", self.serialNumbers[5])
            + struct.pack("<L", self.serialNumbers[6])
            + struct.pack("<L", self.serialNumbers[7])
            + struct.pack("<L", self.serialNumbers[8])
            + struct.pack("<L", self.serialNumbers[9])
            + struct.pack("<L", self.serialNumbers[10])
            + struct.pack("<L", self.serialNumbers[11])
            + struct.pack("<L", self.serialNumbers[12])
            + struct.pack("<L", self.serialNumbers[13])
            + struct.pack("<L", self.serialNumbers[14])
            + struct.pack("<L", self.serialNumbers[15])
            + struct.pack("<L", self.crc32)
        )
    def unpack(self, data) -> None:
        self.serialNumbers = (
            struct.unpack("<L", data[0: 4])[0],
            struct.unpack("<L", data[4: 8])[0],
            struct.unpack("<L", data[8: 12])[0],
            struct.unpack("<L", data[12: 16])[0],
            struct.unpack("<L", data[16: 20])[0],
            struct.unpack("<L", data[20: 24])[0],
            struct.unpack("<L", data[24: 28])[0],
            struct.unpack("<L", data[28: 32])[0],
            struct.unpack("<L", data[32: 36])[0],
            struct.unpack("<L", data[36: 40])[0],
            struct.unpack("<L", data[40: 44])[0],
            struct.unpack("<L", data[44: 48])[0],
            struct.unpack("<L", data[48: 52])[0],
            struct.unpack("<L", data[52: 56])[0],
            struct.unpack("<L", data[56: 60])[0],
            struct.unpack("<L", data[60: 64])[0],
        )
        self.crc32 = struct.unpack("<L", data[64:68])[0]
# SettingsBlock1
@dataclasses.dataclass
class Setting_SettingsBlock1:
    SIZE = 20
    BIT_OFFSETS = {
        'setting1' : 0, #u32
        'setting2' : 32, #u32
        'setting3' : 64, #u32
        'setting4' : 96, #u32
        'crc32' : 128, #u32
     }
    BYTE_OFFSETS = {
        'setting1' : 0, #u32
        'setting2' : 4, #u32
        'setting3' : 8, #u32
        'setting4' : 12, #u32
        'crc32' : 16, #u32
     }
    setting1: int = 0
    setting2: int = 0
    setting3: int = 0
    setting4: int = 0
    crc32: int = 0
    def pack(self) -> bytes:
        return (b''
            + struct.pack("<L", self.setting1)
            + struct.pack("<L", self.setting2)
            + struct.pack("<L", self.setting3)
            + struct.pack("<L", self.setting4)
            + struct.pack("<L", self.crc32)
        )
    def unpack(self, data) -> None:
        self.setting1 = struct.unpack("<L", data[0:4])[0]
        self.setting2 = struct.unpack("<L", data[4:8])[0]
        self.setting3 = struct.unpack("<L", data[8:12])[0]
        self.setting4 = struct.unpack("<L", data[12:16])[0]
        self.crc32 = struct.unpack("<L", data[16:20])[0]
# SettingsBlock2
@dataclasses.dataclass
class Setting_SettingsBlock2:
    SIZE = 12
    BIT_OFFSETS = {
        'ching' : 0, #u32
        'chong' : 32, #u16
        '__pad01' : 48, #u8
        'crc32' : 64, #u32
     }
    BYTE_OFFSETS = {
        'ching' : 0, #u32
        'chong' : 4, #u16
        '__pad01' : 6, #u8
        'crc32' : 8, #u32
     }
    ching: int = 0
    chong: int = 0
    __pad01: Tuple[int] = (0,0,)
    crc32: int = 0
    def pack(self) -> bytes:
        return (b''
            + struct.pack("<L", self.ching)
            + struct.pack("<H", self.chong)
            + struct.pack("<B", self.__pad01[0])
            + struct.pack("<B", self.__pad01[1])
            + struct.pack("<L", self.crc32)
        )
    def unpack(self, data) -> None:
        self.ching = struct.unpack("<L", data[0:4])[0]
        self.chong = struct.unpack("<H", data[4:6])[0]
        self.__pad01 = (
            struct.unpack("<B", data[6: 7])[0],
            struct.unpack("<B", data[7: 8])[0],
        )
        self.crc32 = struct.unpack("<L", data[8:12])[0]
# JabusHeader
@dataclasses.dataclass
class JabusHeader:
    SIZE = 4
    BIT_OFFSETS = {
        'dst' : 0, #u8
        'length' : 8, #u8
        'cmd' : 16, #u16
     }
    BYTE_OFFSETS = {
        'dst' : 0, #u8
        'length' : 1, #u8
        'cmd' : 2, #u16
     }
    dst: int = 0
    length: int = 0
    cmd: int = 0
    def pack(self) -> bytes:
        return struct.pack("<B", self.dst) + struct.pack("<B", self.length) + struct.pack("<H", self.cmd)
    def unpack(self, data) -> None:
        self.dst = struct.unpack("<B", data[0:1])[0]
        self.length = struct.unpack("<B", data[1:2])[0]
        self.cmd = struct.unpack("<H", data[2:4])[0]
# JabusHeaderAnsExtended
@dataclasses.dataclass
class JabusHeaderAnsExtended:
    SIZE = 8
    BIT_OFFSETS = {
        'dst' : 0, #u8
        'length' : 8, #u8
        'cmd' : 16, #u16
        'ext_length' : 32, #u32
     }
    BYTE_OFFSETS = {
        'dst' : 0, #u8
        'length' : 1, #u8
        'cmd' : 2, #u16
        'ext_length' : 4, #u32
     }
    dst: int = 0
    length: int = 0
    cmd: int = 0
    ext_length: int = 0
    def pack(self) -> bytes:
        return (b''
            + struct.pack("<B", self.dst)
            + struct.pack("<B", self.length)
            + struct.pack("<H", self.cmd)
            + struct.pack("<L", self.ext_length)
        )
    def unpack(self, data) -> None:
        self.dst = struct.unpack("<B", data[0:1])[0]
        self.length = struct.unpack("<B", data[1:2])[0]
        self.cmd = struct.unpack("<H", data[2:4])[0]
        self.ext_length = struct.unpack("<L", data[4:8])[0]
# JabusHeaderReqExtended
@dataclasses.dataclass
class JabusHeaderReqExtended:
    SIZE = 12
    BIT_OFFSETS = {
        'dst' : 0, #u8
        'length' : 8, #u8
        'cmd' : 16, #u16
        'ext_length' : 32, #u32
        'ext_address' : 64, #u32
     }
    BYTE_OFFSETS = {
        'dst' : 0, #u8
        'length' : 1, #u8
        'cmd' : 2, #u16
        'ext_length' : 4, #u32
        'ext_address' : 8, #u32
     }
    dst: int = 0
    length: int = 0
    cmd: int = 0
    ext_length: int = 0
    ext_address: int = 0
    def pack(self) -> bytes:
        return (b''
            + struct.pack("<B", self.dst)
            + struct.pack("<B", self.length)
            + struct.pack("<H", self.cmd)
            + struct.pack("<L", self.ext_length)
            + struct.pack("<L", self.ext_address)
        )
    def unpack(self, data) -> None:
        self.dst = struct.unpack("<B", data[0:1])[0]
        self.length = struct.unpack("<B", data[1:2])[0]
        self.cmd = struct.unpack("<H", data[2:4])[0]
        self.ext_length = struct.unpack("<L", data[4:8])[0]
        self.ext_address = struct.unpack("<L", data[8:12])[0]
# LinkerSymbols
@dataclasses.dataclass
class LinkerSymbols:
    SIZE = 44
    BIT_OFFSETS = {
        'text_start' : 0, #ptr32
        'text_end' : 32, #ptr32
        'ram_data_start' : 64, #ptr32
        'ram_data_end' : 96, #ptr32
        'bss_start' : 128, #ptr32
        'bss_end' : 160, #ptr32
        'persistant_ram_start' : 192, #ptr32
        'persistant_ram_end' : 224, #ptr32
        'extbuf_start' : 256, #ptr32
        'extbuf_end' : 288, #ptr32
        'extbuf_size' : 320, #u32
     }
    BYTE_OFFSETS = {
        'text_start' : 0, #ptr32
        'text_end' : 4, #ptr32
        'ram_data_start' : 8, #ptr32
        'ram_data_end' : 12, #ptr32
        'bss_start' : 16, #ptr32
        'bss_end' : 20, #ptr32
        'persistant_ram_start' : 24, #ptr32
        'persistant_ram_end' : 28, #ptr32
        'extbuf_start' : 32, #ptr32
        'extbuf_end' : 36, #ptr32
        'extbuf_size' : 40, #u32
     }
    text_start: int = 0
    text_end: int = 0
    ram_data_start: int = 0
    ram_data_end: int = 0
    bss_start: int = 0
    bss_end: int = 0
    persistant_ram_start: int = 0
    persistant_ram_end: int = 0
    extbuf_start: int = 0
    extbuf_end: int = 0
    extbuf_size: int = 0
    def pack(self) -> bytes:
        return (b''
            + struct.pack("<L", self.text_start)
            + struct.pack("<L", self.text_end)
            + struct.pack("<L", self.ram_data_start)
            + struct.pack("<L", self.ram_data_end)
            + struct.pack("<L", self.bss_start)
            + struct.pack("<L", self.bss_end)
            + struct.pack("<L", self.persistant_ram_start)
            + struct.pack("<L", self.persistant_ram_end)
            + struct.pack("<L", self.extbuf_start)
            + struct.pack("<L", self.extbuf_end)
            + struct.pack("<L", self.extbuf_size)
        )
    def unpack(self, data) -> None:
        self.text_start = struct.unpack("<L", data[0:4])[0]
        self.text_end = struct.unpack("<L", data[4:8])[0]
        self.ram_data_start = struct.unpack("<L", data[8:12])[0]
        self.ram_data_end = struct.unpack("<L", data[12:16])[0]
        self.bss_start = struct.unpack("<L", data[16:20])[0]
        self.bss_end = struct.unpack("<L", data[20:24])[0]
        self.persistant_ram_start = struct.unpack("<L", data[24:28])[0]
        self.persistant_ram_end = struct.unpack("<L", data[28:32])[0]
        self.extbuf_start = struct.unpack("<L", data[32:36])[0]
        self.extbuf_end = struct.unpack("<L", data[36:40])[0]
        self.extbuf_size = struct.unpack("<L", data[40:44])[0]
# ProbeConstantData
@dataclasses.dataclass
class ProbeConstantData:
    SIZE = 9
    BIT_OFFSETS = {
        'jabus_hw_type' : 0, #u8
        'product_table_ptr' : 8, #u32
        'product_table_size' : 40, #u16
        'protocol_product_specific_type' : 56, #u16
     }
    BYTE_OFFSETS = {
        'jabus_hw_type' : 0, #u8
        'product_table_ptr' : 1, #u32
        'product_table_size' : 5, #u16
        'protocol_product_specific_type' : 7, #u16
     }
    jabus_hw_type: int = 0
    product_table_ptr: int = 0
    product_table_size: int = 0
    protocol_product_specific_type: int = 0
    def pack(self) -> bytes:
        return (b''
            + struct.pack("<B", self.jabus_hw_type)
            + struct.pack("<L", self.product_table_ptr)
            + struct.pack("<H", self.product_table_size)
            + struct.pack("<H", self.protocol_product_specific_type)
        )
    def unpack(self, data) -> None:
        self.jabus_hw_type = struct.unpack("<B", data[0:1])[0]
        self.product_table_ptr = struct.unpack("<L", data[1:5])[0]
        self.product_table_size = struct.unpack("<H", data[5:7])[0]
        self.protocol_product_specific_type = struct.unpack("<H", data[7:9])[0]
# Main
@dataclasses.dataclass
class SettingsMain:
    SIZE = 4
    BIT_OFFSETS = {
        'settings1' : 0, #ptr32
        'settings2' : 32, #ptr32
        'serialNumbers' : 64, #ptr32
     }
    BYTE_OFFSETS = {
        'settings1' : 0, #ptr32
        'settings2' : 4, #ptr32
        'serialNumbers' : 8, #ptr32
     }
    settings1: int = 0
    settings2: int = 0
    serialNumbers: int = 0
    def pack(self) -> bytes:
        return struct.pack("<L", self.settings1) + struct.pack("<L", self.settings2) + struct.pack("<L", self.serialNumbers)
    def unpack(self, data) -> None:
        self.settings1 = struct.unpack("<L", data[0:4])[0]
        self.settings2 = struct.unpack("<L", data[4:8])[0]
        self.serialNumbers = struct.unpack("<L", data[8:12])[0]
# Jabus Cmd Echo (0x0004)
# Echo
@dataclasses.dataclass
class JabusRequestEcho:
    CMD_ID = 0x0004
    CMD_NAME = 'Echo'
    CMD_LENGTH = 8
    BIT_OFFSETS = {
        'header' : 0, #struct
        'data' : 32, #u8
     }
    BYTE_OFFSETS = {
        'header' : 0, #struct
        'data' : 4, #u8
     }
    header: JabusHeader = dataclasses.field(default_factory=lambda: JabusHeader(0,JabusRequestEcho.CMD_LENGTH,JabusRequestEcho.CMD_ID))
    data: Tuple[int] = (0,0,0,0,)
    def pack(self) -> bytes:
        return (b''
            + self.header.pack()
            + struct.pack("<B", self.data[0])
            + struct.pack("<B", self.data[1])
            + struct.pack("<B", self.data[2])
            + struct.pack("<B", self.data[3])
        )
    def unpack(self, data) -> None:
        self.header.unpack(data[0:4])
        self.data = (
            struct.unpack("<B", data[4: 5])[0],
            struct.unpack("<B", data[5: 6])[0],
            struct.unpack("<B", data[6: 7])[0],
            struct.unpack("<B", data[7: 8])[0],
        )
# Echo
@dataclasses.dataclass
class JabusAnswerEcho:
    CMD_ID = 0x0004
    CMD_NAME = 'Echo'
    CMD_LENGTH = 8
    BIT_OFFSETS = {
        'header' : 0, #struct
        'data' : 32, #u8
     }
    BYTE_OFFSETS = {
        'header' : 0, #struct
        'data' : 4, #u8
     }
    header: JabusHeader = dataclasses.field(default_factory=lambda: JabusHeader(0,JabusAnswerEcho.CMD_LENGTH,JabusAnswerEcho.CMD_ID))
    data: Tuple[int] = (0,0,0,0,)
    def pack(self) -> bytes:
        return (b''
            + self.header.pack()
            + struct.pack("<B", self.data[0])
            + struct.pack("<B", self.data[1])
            + struct.pack("<B", self.data[2])
            + struct.pack("<B", self.data[3])
        )
    def unpack(self, data) -> None:
        self.header.unpack(data[0:4])
        self.data = (
            struct.unpack("<B", data[4: 5])[0],
            struct.unpack("<B", data[5: 6])[0],
            struct.unpack("<B", data[6: 7])[0],
            struct.unpack("<B", data[7: 8])[0],
        )
# Jabus Cmd EchoExt (0x0006)
# EchoExt
@dataclasses.dataclass
class JabusRequestEchoExt:
    CMD_ID = 0x0007
    CMD_NAME = 'EchoExt'
    CMD_LENGTH = 12
    BIT_OFFSETS = {
        'header' : 0, #struct
     }
    BYTE_OFFSETS = {
        'header' : 0, #struct
     }
    header: JabusHeaderReqExtended = dataclasses.field(default_factory=lambda: JabusHeaderReqExtended(0,JabusRequestEchoExt.CMD_LENGTH,JabusRequestEchoExt.CMD_ID))
    def pack(self) -> bytes:
        return self.header.pack()
    def unpack(self, data) -> None:
        self.header.unpack(data[0:12])
# EchoExt
@dataclasses.dataclass
class JabusAnswerEchoExt:
    CMD_ID = 0x0007
    CMD_NAME = 'EchoExt'
    CMD_LENGTH = 8
    BIT_OFFSETS = {
        'header' : 0, #struct
     }
    BYTE_OFFSETS = {
        'header' : 0, #struct
     }
    header: JabusHeaderAnsExtended = dataclasses.field(default_factory=lambda: JabusHeaderAnsExtended(0,JabusAnswerEchoExt.CMD_LENGTH,JabusAnswerEchoExt.CMD_ID))
    def pack(self) -> bytes:
        return self.header.pack()
    def unpack(self, data) -> None:
        self.header.unpack(data[0:8])
# Jabus Cmd GetExtbufInfo (0x0018)
# GetExtbufInfo
@dataclasses.dataclass
class JabusRequestGetExtbufInfo:
    CMD_ID = 0x0018
    CMD_NAME = 'GetExtbufInfo'
    CMD_LENGTH = 4
    BIT_OFFSETS = {
        'header' : 0, #struct
     }
    BYTE_OFFSETS = {
        'header' : 0, #struct
     }
    header: JabusHeader = dataclasses.field(default_factory=lambda: JabusHeader(0,JabusRequestGetExtbufInfo.CMD_LENGTH,JabusRequestGetExtbufInfo.CMD_ID))
    def pack(self) -> bytes:
        return self.header.pack()
    def unpack(self, data) -> None:
        self.header.unpack(data[0:4])
# GetExtbufInfo
@dataclasses.dataclass
class JabusAnswerGetExtbufInfo:
    CMD_ID = 0x0018
    CMD_NAME = 'GetExtbufInfo'
    CMD_LENGTH = 12
    BIT_OFFSETS = {
        'header' : 0, #struct
        'buf_ptr' : 32, #u32
        'buf_len' : 64, #u32
     }
    BYTE_OFFSETS = {
        'header' : 0, #struct
        'buf_ptr' : 4, #u32
        'buf_len' : 8, #u32
     }
    header: JabusHeader = dataclasses.field(default_factory=lambda: JabusHeader(0,JabusAnswerGetExtbufInfo.CMD_LENGTH,JabusAnswerGetExtbufInfo.CMD_ID))
    buf_ptr: int = 0
    buf_len: int = 0
    def pack(self) -> bytes:
        return self.header.pack() + struct.pack("<L", self.buf_ptr) + struct.pack("<L", self.buf_len)
    def unpack(self, data) -> None:
        self.header.unpack(data[0:4])
        self.buf_ptr = struct.unpack("<L", data[4:8])[0]
        self.buf_len = struct.unpack("<L", data[8:12])[0]
# Jabus Cmd GetFuncPtr (0x001E)
# GetFuncPtr
@dataclasses.dataclass
class JabusRequestGetFuncPtr:
    CMD_ID = 0x001E
    CMD_NAME = 'GetFuncPtr'
    CMD_LENGTH = 4
    BIT_OFFSETS = {
        'header' : 0, #struct
     }
    BYTE_OFFSETS = {
        'header' : 0, #struct
     }
    header: JabusHeader = dataclasses.field(default_factory=lambda: JabusHeader(0,JabusRequestGetFuncPtr.CMD_LENGTH,JabusRequestGetFuncPtr.CMD_ID))
    def pack(self) -> bytes:
        return self.header.pack()
    def unpack(self, data) -> None:
        self.header.unpack(data[0:4])
# GetFuncPtr
@dataclasses.dataclass
class JabusAnswerGetFuncPtr:
    CMD_ID = 0x001E
    CMD_NAME = 'GetFuncPtr'
    CMD_LENGTH = 8
    BIT_OFFSETS = {
        'header' : 0, #struct
        'func' : 32, #u32
     }
    BYTE_OFFSETS = {
        'header' : 0, #struct
        'func' : 4, #u32
     }
    header: JabusHeader = dataclasses.field(default_factory=lambda: JabusHeader(0,JabusAnswerGetFuncPtr.CMD_LENGTH,JabusAnswerGetFuncPtr.CMD_ID))
    func: int = 0
    def pack(self) -> bytes:
        return self.header.pack() + struct.pack("<L", self.func)
    def unpack(self, data) -> None:
        self.header.unpack(data[0:4])
        self.func = struct.unpack("<L", data[4:8])[0]
# Jabus Cmd GetSettingsInfo (0x0010)
# GetSettingsInfo
@dataclasses.dataclass
class JabusRequestGetSettingsInfo:
    CMD_ID = 0x0010
    CMD_NAME = 'GetSettingsInfo'
    CMD_LENGTH = 4
    BIT_OFFSETS = {
        'header' : 0, #struct
     }
    BYTE_OFFSETS = {
        'header' : 0, #struct
     }
    header: JabusHeader = dataclasses.field(default_factory=lambda: JabusHeader(0,JabusRequestGetSettingsInfo.CMD_LENGTH,JabusRequestGetSettingsInfo.CMD_ID))
    def pack(self) -> bytes:
        return self.header.pack()
    def unpack(self, data) -> None:
        self.header.unpack(data[0:4])
# GetSettingsInfo
@dataclasses.dataclass
class JabusAnswerGetSettingsInfo:
    CMD_ID = 0x0010
    CMD_NAME = 'GetSettingsInfo'
    CMD_LENGTH = 8
    BIT_OFFSETS = {
        'header' : 0, #struct
        'num_settings' : 32, #u32
     }
    BYTE_OFFSETS = {
        'header' : 0, #struct
        'num_settings' : 4, #u32
     }
    header: JabusHeader = dataclasses.field(default_factory=lambda: JabusHeader(0,JabusAnswerGetSettingsInfo.CMD_LENGTH,JabusAnswerGetSettingsInfo.CMD_ID))
    num_settings: int = 0
    def pack(self) -> bytes:
        return self.header.pack() + struct.pack("<L", self.num_settings)
    def unpack(self, data) -> None:
        self.header.unpack(data[0:4])
        self.num_settings = struct.unpack("<L", data[4:8])[0]
# Jabus Cmd JumpToMem (0x001C)
# JumpToMem
@dataclasses.dataclass
class JabusRequestJumpToMem:
    CMD_ID = 0x001C
    CMD_NAME = 'JumpToMem'
    CMD_LENGTH = 16
    BIT_OFFSETS = {
        'header' : 0, #struct
        'addr' : 32, #u32
        'arg0' : 64, #i32
        'arg1' : 96, #i32
     }
    BYTE_OFFSETS = {
        'header' : 0, #struct
        'addr' : 4, #u32
        'arg0' : 8, #i32
        'arg1' : 12, #i32
     }
    header: JabusHeader = dataclasses.field(default_factory=lambda: JabusHeader(0,JabusRequestJumpToMem.CMD_LENGTH,JabusRequestJumpToMem.CMD_ID))
    addr: int = 0
    arg0: int = 0
    arg1: int = 0
    def pack(self) -> bytes:
        return (b''
            + self.header.pack()
            + struct.pack("<L", self.addr)
            + struct.pack("<l", self.arg0)
            + struct.pack("<l", self.arg1)
        )
    def unpack(self, data) -> None:
        self.header.unpack(data[0:4])
        self.addr = struct.unpack("<L", data[4:8])[0]
        self.arg0 = struct.unpack("<l", data[8:12])[0]
        self.arg1 = struct.unpack("<l", data[12:16])[0]
# JumpToMem
@dataclasses.dataclass
class JabusAnswerJumpToMem:
    CMD_ID = 0x001C
    CMD_NAME = 'JumpToMem'
    CMD_LENGTH = 8
    BIT_OFFSETS = {
        'header' : 0, #struct
        'result' : 32, #i32
     }
    BYTE_OFFSETS = {
        'header' : 0, #struct
        'result' : 4, #i32
     }
    header: JabusHeader = dataclasses.field(default_factory=lambda: JabusHeader(0,JabusAnswerJumpToMem.CMD_LENGTH,JabusAnswerJumpToMem.CMD_ID))
    result: int = 0
    def pack(self) -> bytes:
        return self.header.pack() + struct.pack("<l", self.result)
    def unpack(self, data) -> None:
        self.header.unpack(data[0:4])
        self.result = struct.unpack("<l", data[4:8])[0]
# Jabus Cmd NOK (0x0002)
# NOK
@dataclasses.dataclass
class JabusRequestNOK:
    CMD_ID = 0x0002
    CMD_NAME = 'NOK'
    CMD_LENGTH = 4
    BIT_OFFSETS = {
        'header' : 0, #struct
     }
    BYTE_OFFSETS = {
        'header' : 0, #struct
     }
    header: JabusHeader = dataclasses.field(default_factory=lambda: JabusHeader(0,JabusRequestNOK.CMD_LENGTH,JabusRequestNOK.CMD_ID))
    def pack(self) -> bytes:
        return self.header.pack()
    def unpack(self, data) -> None:
        self.header.unpack(data[0:4])
# NOK
@dataclasses.dataclass
class JabusAnswerNOK:
    CMD_ID = 0x0002
    CMD_NAME = 'NOK'
    CMD_LENGTH = 14
    BIT_OFFSETS = {
        'header' : 0, #struct
        'the_bad_cmd' : 32, #u16
        'error_code' : 48, #i32
        'info' : 80, #u32
     }
    BYTE_OFFSETS = {
        'header' : 0, #struct
        'the_bad_cmd' : 4, #u16
        'error_code' : 6, #i32
        'info' : 10, #u32
     }
    header: JabusHeader = dataclasses.field(default_factory=lambda: JabusHeader(0,JabusAnswerNOK.CMD_LENGTH,JabusAnswerNOK.CMD_ID))
    the_bad_cmd: int = 0
    error_code: int = 0
    info: int = 0
    def pack(self) -> bytes:
        return (b''
            + self.header.pack()
            + struct.pack("<H", self.the_bad_cmd)
            + struct.pack("<l", self.error_code)
            + struct.pack("<L", self.info)
        )
    def unpack(self, data) -> None:
        self.header.unpack(data[0:4])
        self.the_bad_cmd = struct.unpack("<H", data[4:6])[0]
        self.error_code = struct.unpack("<l", data[6:10])[0]
        self.info = struct.unpack("<L", data[10:14])[0]
# Jabus Cmd ReadMem (0x000A)
# ReadMem
@dataclasses.dataclass
class JabusRequestReadMem:
    CMD_ID = 0x000A
    CMD_NAME = 'ReadMem'
    CMD_LENGTH = 10
    BIT_OFFSETS = {
        'header' : 0, #struct
        'addr' : 32, #u32
        'length' : 64, #u16
     }
    BYTE_OFFSETS = {
        'header' : 0, #struct
        'addr' : 4, #u32
        'length' : 8, #u16
     }
    header: JabusHeader = dataclasses.field(default_factory=lambda: JabusHeader(0,JabusRequestReadMem.CMD_LENGTH,JabusRequestReadMem.CMD_ID))
    addr: int = 0
    length: int = 0
    def pack(self) -> bytes:
        return self.header.pack() + struct.pack("<L", self.addr) + struct.pack("<H", self.length)
    def unpack(self, data) -> None:
        self.header.unpack(data[0:4])
        self.addr = struct.unpack("<L", data[4:8])[0]
        self.length = struct.unpack("<H", data[8:10])[0]
# ReadMem
@dataclasses.dataclass
class JabusAnswerReadMem:
    CMD_ID = 0x000B
    CMD_NAME = 'ReadMem'
    CMD_LENGTH = 8
    BIT_OFFSETS = {
        'header' : 0, #struct
     }
    BYTE_OFFSETS = {
        'header' : 0, #struct
     }
    header: JabusHeaderAnsExtended = dataclasses.field(default_factory=lambda: JabusHeaderAnsExtended(0,JabusAnswerReadMem.CMD_LENGTH,JabusAnswerReadMem.CMD_ID))
    def pack(self) -> bytes:
        return self.header.pack()
    def unpack(self, data) -> None:
        self.header.unpack(data[0:8])
# Jabus Cmd ReadSettingsBlock (0x0012)
# ReadSettingsBlock
@dataclasses.dataclass
class JabusRequestReadSettingsBlock:
    CMD_ID = 0x0012
    CMD_NAME = 'ReadSettingsBlock'
    CMD_LENGTH = 8
    BIT_OFFSETS = {
        'header' : 0, #struct
        'block_index' : 32, #u32
     }
    BYTE_OFFSETS = {
        'header' : 0, #struct
        'block_index' : 4, #u32
     }
    header: JabusHeader = dataclasses.field(default_factory=lambda: JabusHeader(0,JabusRequestReadSettingsBlock.CMD_LENGTH,JabusRequestReadSettingsBlock.CMD_ID))
    block_index: int = 0
    def pack(self) -> bytes:
        return self.header.pack() + struct.pack("<L", self.block_index)
    def unpack(self, data) -> None:
        self.header.unpack(data[0:4])
        self.block_index = struct.unpack("<L", data[4:8])[0]
# ReadSettingsBlock
@dataclasses.dataclass
class JabusAnswerReadSettingsBlock:
    CMD_ID = 0x0013
    CMD_NAME = 'ReadSettingsBlock'
    CMD_LENGTH = 12
    BIT_OFFSETS = {
        'header' : 0, #struct
        'block_index' : 64, #u32
     }
    BYTE_OFFSETS = {
        'header' : 0, #struct
        'block_index' : 8, #u32
     }
    header: JabusHeaderAnsExtended = dataclasses.field(default_factory=lambda: JabusHeaderAnsExtended(0,JabusAnswerReadSettingsBlock.CMD_LENGTH,JabusAnswerReadSettingsBlock.CMD_ID))
    block_index: int = 0
    def pack(self) -> bytes:
        return self.header.pack() + struct.pack("<L", self.block_index)
    def unpack(self, data) -> None:
        self.header.unpack(data[0:8])
        self.block_index = struct.unpack("<L", data[8:12])[0]
# Jabus Cmd Reset (0x0008)
# Reset
@dataclasses.dataclass
class JabusRequestReset:
    CMD_ID = 0x0008
    CMD_NAME = 'Reset'
    CMD_LENGTH = 8
    BIT_OFFSETS = {
        'header' : 0, #struct
        'reset_mode_magic' : 32, #u32
     }
    BYTE_OFFSETS = {
        'header' : 0, #struct
        'reset_mode_magic' : 4, #u32
     }
    header: JabusHeader = dataclasses.field(default_factory=lambda: JabusHeader(0,JabusRequestReset.CMD_LENGTH,JabusRequestReset.CMD_ID))
    reset_mode_magic: int = 0
    def pack(self) -> bytes:
        return self.header.pack() + struct.pack("<L", self.reset_mode_magic)
    def unpack(self, data) -> None:
        self.header.unpack(data[0:4])
        self.reset_mode_magic = struct.unpack("<L", data[4:8])[0]
# Reset
@dataclasses.dataclass
class JabusAnswerReset:
    CMD_ID = 0x0008
    CMD_NAME = 'Reset'
    CMD_LENGTH = 12
    BIT_OFFSETS = {
        'header' : 0, #struct
        'reset_mode_magic' : 32, #u32
        'reset_counter' : 64, #u32
     }
    BYTE_OFFSETS = {
        'header' : 0, #struct
        'reset_mode_magic' : 4, #u32
        'reset_counter' : 8, #u32
     }
    header: JabusHeader = dataclasses.field(default_factory=lambda: JabusHeader(0,JabusAnswerReset.CMD_LENGTH,JabusAnswerReset.CMD_ID))
    reset_mode_magic: int = 0
    reset_counter: int = 0
    def pack(self) -> bytes:
        return self.header.pack() + struct.pack("<L", self.reset_mode_magic) + struct.pack("<L", self.reset_counter)
    def unpack(self, data) -> None:
        self.header.unpack(data[0:4])
        self.reset_mode_magic = struct.unpack("<L", data[4:8])[0]
        self.reset_counter = struct.unpack("<L", data[8:12])[0]
# Jabus Cmd WriteMem (0x000C)
# WriteMem
@dataclasses.dataclass
class JabusRequestWriteMem:
    CMD_ID = 0x000D
    CMD_NAME = 'WriteMem'
    CMD_LENGTH = 12
    BIT_OFFSETS = {
        'header' : 0, #struct
     }
    BYTE_OFFSETS = {
        'header' : 0, #struct
     }
    header: JabusHeaderReqExtended = dataclasses.field(default_factory=lambda: JabusHeaderReqExtended(0,JabusRequestWriteMem.CMD_LENGTH,JabusRequestWriteMem.CMD_ID))
    def pack(self) -> bytes:
        return self.header.pack()
    def unpack(self, data) -> None:
        self.header.unpack(data[0:12])
# WriteMem
@dataclasses.dataclass
class JabusAnswerWriteMem:
    CMD_ID = 0x000C
    CMD_NAME = 'WriteMem'
    CMD_LENGTH = 4
    BIT_OFFSETS = {
        'header' : 0, #struct
     }
    BYTE_OFFSETS = {
        'header' : 0, #struct
     }
    header: JabusHeader = dataclasses.field(default_factory=lambda: JabusHeader(0,JabusAnswerWriteMem.CMD_LENGTH,JabusAnswerWriteMem.CMD_ID))
    def pack(self) -> bytes:
        return self.header.pack()
    def unpack(self, data) -> None:
        self.header.unpack(data[0:4])
# Jabus Cmd GetLinkerSymbols (0x001A)
# GetLinkerSymbols
@dataclasses.dataclass
class JabusRequestGetLinkerSymbols:
    CMD_ID = 0x001A
    CMD_NAME = 'GetLinkerSymbols'
    CMD_LENGTH = 4
    BIT_OFFSETS = {
        'header' : 0, #struct
     }
    BYTE_OFFSETS = {
        'header' : 0, #struct
     }
    header: JabusHeader = dataclasses.field(default_factory=lambda: JabusHeader(0,JabusRequestGetLinkerSymbols.CMD_LENGTH,JabusRequestGetLinkerSymbols.CMD_ID))
    def pack(self) -> bytes:
        return self.header.pack()
    def unpack(self, data) -> None:
        self.header.unpack(data[0:4])
# GetLinkerSymbols
@dataclasses.dataclass
class JabusAnswerGetLinkerSymbols:
    CMD_ID = 0x001A
    CMD_NAME = 'GetLinkerSymbols'
    CMD_LENGTH = 48
    BIT_OFFSETS = {
        'header' : 0, #struct
        'linker_symbols' : 32, #struct
     }
    BYTE_OFFSETS = {
        'header' : 0, #struct
        'linker_symbols' : 4, #struct
     }
    header: JabusHeader = dataclasses.field(default_factory=lambda: JabusHeader(0,JabusAnswerGetLinkerSymbols.CMD_LENGTH,JabusAnswerGetLinkerSymbols.CMD_ID))
    linker_symbols: LinkerSymbols = dataclasses.field(default_factory=LinkerSymbols)
    def pack(self) -> bytes:
        return self.header.pack() + self.linker_symbols.pack()
    def unpack(self, data) -> None:
        self.header.unpack(data[0:4])
        self.linker_symbols.unpack(data[4:48])
# Jabus Cmd Probe (0x0000)
# Probe
@dataclasses.dataclass
class JabusRequestProbe:
    CMD_ID = 0x0000
    CMD_NAME = 'Probe'
    CMD_LENGTH = 4
    BIT_OFFSETS = {
        'header' : 0, #struct
     }
    BYTE_OFFSETS = {
        'header' : 0, #struct
     }
    header: JabusHeader = dataclasses.field(default_factory=lambda: JabusHeader(0,JabusRequestProbe.CMD_LENGTH,JabusRequestProbe.CMD_ID))
    def pack(self) -> bytes:
        return self.header.pack()
    def unpack(self, data) -> None:
        self.header.unpack(data[0:4])
# Probe
@dataclasses.dataclass
class JabusAnswerProbe:
    CMD_ID = 0x0000
    CMD_NAME = 'Probe'
    CMD_LENGTH = 16
    BIT_OFFSETS = {
        'header' : 0, #struct
        'main_cpu_nr' : 32, #u8
        'op_flags' : 40, #u16
        'cdata' : 56, #struct
     }
    BYTE_OFFSETS = {
        'header' : 0, #struct
        'main_cpu_nr' : 4, #u8
        'op_flags' : 5, #u16
        'cdata' : 7, #struct
     }
    header: JabusHeader = dataclasses.field(default_factory=lambda: JabusHeader(0,JabusAnswerProbe.CMD_LENGTH,JabusAnswerProbe.CMD_ID))
    main_cpu_nr: int = 0
    op_flags: int = 0
    cdata: ProbeConstantData = dataclasses.field(default_factory=ProbeConstantData)
    def pack(self) -> bytes:
        return (b''
            + self.header.pack()
            + struct.pack("<B", self.main_cpu_nr)
            + struct.pack("<H", self.op_flags)
            + self.cdata.pack()
        )
    def unpack(self, data) -> None:
        self.header.unpack(data[0:4])
        self.main_cpu_nr = struct.unpack("<B", data[4:5])[0]
        self.op_flags = struct.unpack("<H", data[5:7])[0]
        self.cdata.unpack(data[7:16])
# enum FATAL_ERROR_CODE no ctypes
# enum JABUS_CMD_HANDLER_RET no ctypes
# enum MAIN_STATE no ctypes
# enum RESET_MODE no ctypes
# enum STARTUP_REASON no ctypes
# bitdef PROBE_OP_FLAGS no ctypes
# ctypes SerialNumbers
class Setting_SerialNumbers_ct(ctypes.Structure):
    _fields_ = [
        ("serialNumbers"     , (ctypes.c_uint * 16)), # 0
        ("crc32"             , ctypes.c_uint), # 64
    ]
# ctypes SettingsBlock1
class Setting_SettingsBlock1_ct(ctypes.Structure):
    _fields_ = [
        ("setting1"          , ctypes.c_uint), # 0
        ("setting2"          , ctypes.c_uint), # 4
        ("setting3"          , ctypes.c_uint), # 8
        ("setting4"          , ctypes.c_uint), # 12
        ("crc32"             , ctypes.c_uint), # 16
    ]
# ctypes SettingsBlock2
class Setting_SettingsBlock2_ct(ctypes.Structure):
    _fields_ = [
        ("ching"             , ctypes.c_uint), # 0
        ("chong"             , ctypes.c_ushort), # 4
        ("__pad01"           , (ctypes.c_ubyte * 2)), # 6
        ("crc32"             , ctypes.c_uint), # 8
    ]
# ctypes JabusHeader
class JabusHeader_ct(ctypes.Structure):
    _fields_ = [
        ("dst"               , ctypes.c_ubyte), # 0
        ("length"            , ctypes.c_ubyte), # 1
        ("cmd"               , ctypes.c_ushort), # 2
    ]
# ctypes JabusHeaderAnsExtended
class JabusHeaderAnsExtended_ct(ctypes.Structure):
    _fields_ = [
        ("dst"               , ctypes.c_ubyte), # 0
        ("length"            , ctypes.c_ubyte), # 1
        ("cmd"               , ctypes.c_ushort), # 2
        ("ext_length"        , ctypes.c_uint), # 4
    ]
# ctypes JabusHeaderReqExtended
class JabusHeaderReqExtended_ct(ctypes.Structure):
    _fields_ = [
        ("dst"               , ctypes.c_ubyte), # 0
        ("length"            , ctypes.c_ubyte), # 1
        ("cmd"               , ctypes.c_ushort), # 2
        ("ext_length"        , ctypes.c_uint), # 4
        ("ext_address"       , ctypes.c_uint), # 8
    ]
# ctypes LinkerSymbols
class LinkerSymbols_ct(ctypes.Structure):
    _fields_ = [
        ("text_start"        , ctypes.c_void_p), # 0
        ("text_end"          , ctypes.c_void_p), # 4
        ("ram_data_start"    , ctypes.c_void_p), # 8
        ("ram_data_end"      , ctypes.c_void_p), # 12
        ("bss_start"         , ctypes.c_void_p), # 16
        ("bss_end"           , ctypes.c_void_p), # 20
        ("persistant_ram_start", ctypes.c_void_p), # 24
        ("persistant_ram_end", ctypes.c_void_p), # 28
        ("extbuf_start"      , ctypes.c_void_p), # 32
        ("extbuf_end"        , ctypes.c_void_p), # 36
        ("extbuf_size"       , ctypes.c_uint), # 40
    ]
# ctypes ProbeConstantData
class ProbeConstantData_ct(ctypes.Structure):
    _fields_ = [
        ("jabus_hw_type"     , ctypes.c_ubyte), # 0
        ("product_table_ptr" , ctypes.c_uint), # 1
        ("product_table_size", ctypes.c_ushort), # 5
        ("protocol_product_specific_type", ctypes.c_ushort), # 7
    ]
# ctypes Main
class SettingsMain_ct(ctypes.Structure):
    _fields_ = [
        ("settings1"         , ctypes.POINTER(Setting_SettingsBlock1_ct)), # 0
        ("settings2"         , ctypes.POINTER(Setting_SettingsBlock2_ct)), # 4
        ("serialNumbers"     , ctypes.POINTER(Setting_SerialNumbers_ct)), # 8
    ]
# Default BlockHandler.gen_py2: jabus_cmd Echo:
# Default BlockHandler.gen_py2: jabus_cmd EchoExt:
# Default BlockHandler.gen_py2: jabus_cmd GetExtbufInfo:
# Default BlockHandler.gen_py2: jabus_cmd GetFuncPtr:
# Default BlockHandler.gen_py2: jabus_cmd GetSettingsInfo:
# Default BlockHandler.gen_py2: jabus_cmd JumpToMem:
# Default BlockHandler.gen_py2: jabus_cmd NOK:
# Default BlockHandler.gen_py2: jabus_cmd ReadMem:
# Default BlockHandler.gen_py2: jabus_cmd ReadSettingsBlock:
# Default BlockHandler.gen_py2: jabus_cmd Reset:
# Default BlockHandler.gen_py2: jabus_cmd WriteMem:
# Default BlockHandler.gen_py2: jabus_cmd GetLinkerSymbols:
# Default BlockHandler.gen_py2: jabus_cmd Probe:

JABUS_CMDS_MAP = {
    0x0004: (JabusRequestEcho              , JabusAnswerEcho               ),
    0x0005: (JabusRequestEcho              , JabusAnswerEcho               ), # extended versions
    0x0006: (JabusRequestEchoExt           , JabusAnswerEchoExt            ),
    0x0007: (JabusRequestEchoExt           , JabusAnswerEchoExt            ), # extended versions
    0x0018: (JabusRequestGetExtbufInfo     , JabusAnswerGetExtbufInfo      ),
    0x0019: (JabusRequestGetExtbufInfo     , JabusAnswerGetExtbufInfo      ), # extended versions
    0x001E: (JabusRequestGetFuncPtr        , JabusAnswerGetFuncPtr         ),
    0x001F: (JabusRequestGetFuncPtr        , JabusAnswerGetFuncPtr         ), # extended versions
    0x0010: (JabusRequestGetSettingsInfo   , JabusAnswerGetSettingsInfo    ),
    0x0011: (JabusRequestGetSettingsInfo   , JabusAnswerGetSettingsInfo    ), # extended versions
    0x001C: (JabusRequestJumpToMem         , JabusAnswerJumpToMem          ),
    0x001D: (JabusRequestJumpToMem         , JabusAnswerJumpToMem          ), # extended versions
    0x0002: (JabusRequestNOK               , JabusAnswerNOK                ),
    0x0003: (JabusRequestNOK               , JabusAnswerNOK                ), # extended versions
    0x000A: (JabusRequestReadMem           , JabusAnswerReadMem            ),
    0x000B: (JabusRequestReadMem           , JabusAnswerReadMem            ), # extended versions
    0x0012: (JabusRequestReadSettingsBlock , JabusAnswerReadSettingsBlock  ),
    0x0013: (JabusRequestReadSettingsBlock , JabusAnswerReadSettingsBlock  ), # extended versions
    0x0008: (JabusRequestReset             , JabusAnswerReset              ),
    0x0009: (JabusRequestReset             , JabusAnswerReset              ), # extended versions
    0x000C: (JabusRequestWriteMem          , JabusAnswerWriteMem           ),
    0x000D: (JabusRequestWriteMem          , JabusAnswerWriteMem           ), # extended versions
    0x001A: (JabusRequestGetLinkerSymbols  , JabusAnswerGetLinkerSymbols   ),
    0x001B: (JabusRequestGetLinkerSymbols  , JabusAnswerGetLinkerSymbols   ), # extended versions
    0x0000: (JabusRequestProbe             , JabusAnswerProbe              ),
    0x0001: (JabusRequestProbe             , JabusAnswerProbe              ), # extended versions
}
