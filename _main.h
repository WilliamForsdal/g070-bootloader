// auto generated by dsg2.py, SRC002-103 commit hash 0dc1170608c2bd3cdfd7ef880b9ef2ec3bc65201
// Run with args: ['C:\\dev\\src002-103\\dsg2.py', '_main.dsg', '--gen_h', '--gen_c', '--gen_py']
#ifndef INC_GUARD__MAIN
#define INC_GUARD__MAIN

#include <stdint.h>

#if !__cplusplus
typedef int32_t fp1616_t;
typedef int32_t fp0824_t;
#else  // C++
    #error not supported
#endif

#ifndef PACKED
#define PACKED  __attribute__ ((__packed__))
#endif

// constants



// normal blocks
// Enum JABUS_CMD_HANDLER_RET(i32)
#define DSG_ENUM_JABUS_CMD_HANDLER_RET_OK 0
#define DSG_ENUM_JABUS_CMD_HANDLER_RET_NOK -1
#define DSG_ENUM_JABUS_CMD_HANDLER_RET_NOK_EXTDATA_FCS -2
#define DSG_ENUM_JABUS_CMD_HANDLER_RET_NOT_IMPLEMENTED -100

// bitdef PROBE_OP_FLAGS(u16)
#define DSG_PROBE_OP_FLAGS_IN_SMALL_BOOTLOADER_BIT         0
#define DSG_PROBE_OP_FLAGS_IN_SMALL_BOOTLOADER_MASK        0x00000001
#define DSG_PROBE_OP_FLAGS_IN_BIG_BOOTLOADER_BIT           1
#define DSG_PROBE_OP_FLAGS_IN_BIG_BOOTLOADER_MASK          0x00000002
#define DSG_PROBE_OP_FLAGS_SETTINGS_WRITE_OK_BIT           2
#define DSG_PROBE_OP_FLAGS_SETTINGS_WRITE_OK_MASK          0x00000004
#define DSG_PROBE_OP_FLAGS_ROUTING_OK_BIT                  3
#define DSG_PROBE_OP_FLAGS_ROUTING_OK_MASK                 0x00000008
#define DSG_PROBE_OP_FLAGS_NORMAL_OP_BIT                   4
#define DSG_PROBE_OP_FLAGS_NORMAL_OP_MASK                  0x00000010
#define DSG_PROBE_OP_FLAGS_FATAL_ERROR_BIT                 5
#define DSG_PROBE_OP_FLAGS_FATAL_ERROR_MASK                0x00000020
#define DSG_PROBE_OP_FLAGS_HALF_DUPLEX_BIT                 6
#define DSG_PROBE_OP_FLAGS_HALF_DUPLEX_MASK                0x00000040
#define DSG_PROBE_OP_FLAGS_RESTART_NEEDS_FF_BIT            7
#define DSG_PROBE_OP_FLAGS_RESTART_NEEDS_FF_MASK           0x00000080
#define DSG_PROBE_OP_FLAGS_FLOW_CTRL_BIT                   8
#define DSG_PROBE_OP_FLAGS_FLOW_CTRL_MASK                  0x00000100

// settings_block SerialNumbers
struct Setting_SerialNumbers
{
    uint32_t serialNumbers[16];    // 0
    uint32_t crc32;                // 64
}; // size=68, align=4
// settings_block SettingsBlock1
struct Setting_SettingsBlock1
{
    uint32_t setting1;             // 0
    uint32_t setting2;             // 4
    uint32_t setting3;             // 8
    uint32_t setting4;             // 12
    uint32_t crc32;                // 16
}; // size=20, align=4
// settings_block SettingsBlock2
struct Setting_SettingsBlock2
{
    uint32_t ching;                // 0
    uint16_t chong;                // 4
    uint8_t __pad01[2];            // 6
    uint32_t crc32;                // 8
}; // size=12, align=4
// struct JabusHeader
struct PACKED JabusHeader
{
    uint8_t dst;                   // 0
    uint8_t length;                // 1
    uint16_t cmd;                  // 2
}; // size=4, align=1
// struct JabusHeaderAnsExtended
struct PACKED JabusHeaderAnsExtended
{
    uint8_t dst;                   // 0
    uint8_t length;                // 1
    uint16_t cmd;                  // 2
    uint32_t ext_length;           // 4
}; // size=8, align=1
// struct JabusHeaderReqExtended
struct PACKED JabusHeaderReqExtended
{
    uint8_t dst;                   // 0
    uint8_t length;                // 1
    uint16_t cmd;                  // 2
    uint32_t ext_length;           // 4
    uint32_t ext_address;          // 8
}; // size=12, align=1
// struct ProbeConstantData
struct PACKED ProbeConstantData
{
    uint8_t jabus_hw_type;         // 0
    uint32_t product_table_ptr;    // 1
    uint16_t product_table_size;   // 5
    uint16_t protocol_product_specific_type; // 7
}; // size=9, align=1
// settings_collection Main

#define SETTINGS_COLLECTION_MAIN_NUM_BLOCKS 3

#define SETTINGS_MAIN_BLOCK_IDX_SETTINGS1                      0
#define SETTINGS_MAIN_BLOCK_IDX_SETTINGS2                      1
#define SETTINGS_MAIN_BLOCK_IDX_SERIAL_NUMBERS                 2
struct SettingsMain
{
    struct Setting_SettingsBlock1 *settings1; // 0
    struct Setting_SettingsBlock2 *settings2; // 4
    struct Setting_SerialNumbers *serialNumbers; // 8
}; // size=4, align=1
// union MainUnion
union SettingsUnionMain
{
    struct Setting_SettingsBlock1 settings1; // 0
    struct Setting_SettingsBlock2 settings2; // 0
    struct Setting_SerialNumbers serialNumbers; // 0
}; // size=68, align=0
// Jabus Cmd Echo (0x0004)
// struct Echo
struct PACKED JabusRequestEcho
{
    struct JabusHeader header;     // 0
    uint8_t data[4];               // 4
}; // size=8, align=0
// struct Echo
struct PACKED JabusAnswerEcho
{
    struct JabusHeader header;     // 0
    uint8_t data[4];               // 4
}; // size=8, align=0
// Jabus Cmd EchoExt (0x0006)
// struct EchoExt
struct PACKED JabusRequestEchoExt
{
    struct JabusHeaderReqExtended header; // 0
}; // size=12, align=0
// struct EchoExt
struct PACKED JabusAnswerEchoExt
{
    struct JabusHeaderAnsExtended header; // 0
}; // size=8, align=0
// Jabus Cmd GetExtbufInfo (0x0008)
// struct GetExtbufInfo
struct PACKED JabusRequestGetExtbufInfo
{
    struct JabusHeader header;     // 0
}; // size=4, align=0
// struct GetExtbufInfo
struct PACKED JabusAnswerGetExtbufInfo
{
    struct JabusHeader header;     // 0
    uint32_t buf_ptr;              // 4
    uint32_t buf_len;              // 8
}; // size=12, align=0
// Jabus Cmd NOK (0x0002)
// struct NOK
struct PACKED JabusRequestNOK
{
    struct JabusHeader header;     // 0
}; // size=4, align=0
// struct NOK
struct PACKED JabusAnswerNOK
{
    struct JabusHeader header;     // 0
    uint16_t the_bad_cmd;          // 4
    int32_t error_code;            // 6
    uint32_t info;                 // 10
}; // size=14, align=0
// Jabus Cmd ReadMem (0x0010)
// struct ReadMem
struct PACKED JabusRequestReadMem
{
    struct JabusHeader header;     // 0
    uint32_t addr;                 // 4
    uint16_t length;               // 8
}; // size=10, align=0
// struct ReadMem
struct PACKED JabusAnswerReadMem
{
    struct JabusHeaderAnsExtended header; // 0
}; // size=8, align=0
// Jabus Cmd Probe (0x0000)
// struct Probe
struct PACKED JabusRequestProbe
{
    struct JabusHeader header;     // 0
}; // size=4, align=0
// struct Probe
struct PACKED JabusAnswerProbe
{
    struct JabusHeader header;     // 0
    uint8_t main_cpu_nr;           // 4
    uint16_t op_flags;             // 5
    struct ProbeConstantData cdata; // 7
}; // size=16, align=0

// bitbanding
// enum enum JABUS_CMD_HANDLER_RET: no bitbanding for this type
// bitdef bitdef PROBE_OP_FLAGS: no bitbanding for this type
// settings_block SerialNumbers_BB
struct Setting_SerialNumbers_BB
{
    uint32_t serialNumbers[16][32];
    uint32_t crc32[32];
}; // size=68, align=4
// settings_block SettingsBlock1_BB
struct Setting_SettingsBlock1_BB
{
    uint32_t setting1[32];
    uint32_t setting2[32];
    uint32_t setting3[32];
    uint32_t setting4[32];
    uint32_t crc32[32];
}; // size=20, align=4
// settings_block SettingsBlock2_BB
struct Setting_SettingsBlock2_BB
{
    uint32_t ching[32];
    uint32_t chong[16];
    uint32_t __pad01[2][8];
    uint32_t crc32[32];
}; // size=12, align=4
// struct JabusHeader_BB
struct JabusHeader_BB
{
    uint32_t dst[8];
    uint32_t length[8];
    uint32_t cmd[16];
}; // size=4, align=1
// struct JabusHeaderAnsExtended_BB
struct JabusHeaderAnsExtended_BB
{
    uint32_t dst[8];
    uint32_t length[8];
    uint32_t cmd[16];
    uint32_t ext_length[32];
}; // size=8, align=1
// struct JabusHeaderReqExtended_BB
struct JabusHeaderReqExtended_BB
{
    uint32_t dst[8];
    uint32_t length[8];
    uint32_t cmd[16];
    uint32_t ext_length[32];
    uint32_t ext_address[32];
}; // size=12, align=1
// struct ProbeConstantData_BB
struct ProbeConstantData_BB
{
    uint32_t jabus_hw_type[8];
    uint32_t product_table_ptr[32];
    uint32_t product_table_size[16];
    uint32_t protocol_product_specific_type[16];
}; // size=9, align=1
// settings_collection Main_BB
struct SettingsMain_BB
{
    uint32_t settings1[32];
    uint32_t settings2[32];
    uint32_t serialNumbers[32];
}; // size=4, align=1
// union MainUnion_BB
union SettingsUnionMain_BB
{
    struct Setting_SettingsBlock1_BB settings1;
    struct Setting_SettingsBlock2_BB settings2;
    struct Setting_SerialNumbers_BB serialNumbers;
}; // size=68, align=0
// jabus_cmd jabus_cmd Echo: no bitbanding for this type
// jabus_cmd jabus_cmd EchoExt: no bitbanding for this type
// jabus_cmd jabus_cmd GetExtbufInfo: no bitbanding for this type
// jabus_cmd jabus_cmd NOK: no bitbanding for this type
// jabus_cmd jabus_cmd ReadMem: no bitbanding for this type
// jabus_cmd jabus_cmd Probe: no bitbanding for this type
union PACKED JabusCommands
{
  struct JabusRequestEcho reqEcho;
  struct JabusAnswerEcho ansEcho;
  struct JabusRequestEchoExt reqEchoExt;
  struct JabusAnswerEchoExt ansEchoExt;
  struct JabusRequestGetExtbufInfo reqGetExtbufInfo;
  struct JabusAnswerGetExtbufInfo ansGetExtbufInfo;
  struct JabusRequestNOK reqNOK;
  struct JabusAnswerNOK ansNOK;
  struct JabusRequestReadMem reqReadMem;
  struct JabusAnswerReadMem ansReadMem;
  struct JabusRequestProbe reqProbe;
  struct JabusAnswerProbe ansProbe;
};
#define JABUS_CMD_ECHO                 0x0004
#define JABUS_CMD_ECHO_EXT             0x0006
#define JABUS_CMD_GET_EXTBUF_INFO      0x0008
#define JABUS_CMD_NOK                  0x0002
#define JABUS_CMD_READ_MEM             0x0010
#define JABUS_CMD_PROBE                0x0000


union PACKED JabusBufferUnion {
    struct PACKED JabusHeader header;
    struct PACKED JabusHeaderReqExtended header_req_ext;
    struct PACKED JabusHeaderAnsExtended header_ans_ext;
    union JabusCommands cmds;
    uint8_t data[sizeof(union JabusCommands) + 2]; // +2 for FCS
    uint16_t u16header[2];                         // for fletcher, we want to initialize c0/c1 with header data.
};

union u32_b {
    uint32_t u32;
    uint16_t u16[2];
    uint8_t u8[4];
};

struct JabusState {
    int state;
    int got_len;
    int got_pkt;
    union JabusBufferUnion *buf;
    uint32_t fcs0;
    uint32_t fcs1;
    int fletcher_count;
    uint8_t *ext_ptr; 
    uint32_t ext_down_count;
    union u32_b fcs32_tmp;
};
int jabus_pkt_handler_autogen(uint16_t cmd, struct JabusState *js);
int jabus_cmd_handler_echo(struct JabusState* state, struct JabusRequestEcho *req);
int jabus_cmd_handler_echo_ext(struct JabusState* state, struct JabusRequestEchoExt *req);
int jabus_cmd_handler_get_extbuf_info(struct JabusState* state, struct JabusRequestGetExtbufInfo *req);
int jabus_cmd_handler_nok(struct JabusState* state, struct JabusRequestNOK *req);
int jabus_cmd_handler_read_mem(struct JabusState* state, struct JabusRequestReadMem *req);
int jabus_cmd_handler_probe(struct JabusState* state, struct JabusRequestProbe *req);

#endif // include guard
