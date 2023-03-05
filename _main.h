// auto generated by dsg2.py, SRC002-103 commit hash 5e20944d0a8e2155895f049c8892b67c9178f8df
// Run with args: ['C:\\dev\\src002-103\\dsg2.py', '.\\_main.dsg', '--gen_h']
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
// struct ProductionDataHeader
struct PACKED ProductionDataHeader
{
    uint32_t magic;                // 0
    uint16_t pd_size;              // 4
    uint8_t hw_version;            // 6
    uint8_t pad;                   // 7
    uint32_t production_date;      // 8
}; // size=12, align=1
// struct Memmap
struct Memmap
{
    struct ProbeConstantData probe_cdata; // 0
}; // size=9, align=1
// Jabus Cmd Control (0x0012)
// struct Control
struct PACKED JabusRequestControl
{
    struct JabusHeader header;     // 0
    uint8_t led_state1;            // 4
    uint8_t pad1[3];               // 5
}; // size=8, align=0
// struct Control
struct PACKED JabusAnswerControl
{
    struct JabusHeader header;     // 0
}; // size=4, align=0
// Jabus Cmd GetSysTickMs (0x0014)
// struct GetSysTickMs
struct PACKED JabusRequestGetSysTickMs
{
    struct JabusHeader header;     // 0
}; // size=4, align=0
// struct GetSysTickMs
struct PACKED JabusAnswerGetSysTickMs
{
    struct JabusHeader header;     // 0
    uint32_t ticks;                // 4
}; // size=8, align=0
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
// bitdef bitdef PROBE_OP_FLAGS: no bitbanding for this type
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
// struct ProductionDataHeader_BB
struct ProductionDataHeader_BB
{
    uint32_t magic[32];
    uint32_t pd_size[16];
    uint32_t hw_version[8];
    uint32_t pad[8];
    uint32_t production_date[32];
}; // size=12, align=1
// struct Memmap_BB
struct Memmap_BB
{
    struct ProbeConstantData_BB probe_cdata;
}; // size=9, align=1
// jabus_cmd jabus_cmd Control: no bitbanding for this type
// jabus_cmd jabus_cmd GetSysTickMs: no bitbanding for this type
// jabus_cmd jabus_cmd NOK: no bitbanding for this type
// jabus_cmd jabus_cmd Probe: no bitbanding for this type
union PACKED JabusCommands
{
  struct JabusRequestControl reqControl;
  struct JabusAnswerControl ansControl;
  struct JabusRequestGetSysTickMs reqGetSysTickMs;
  struct JabusAnswerGetSysTickMs ansGetSysTickMs;
  struct JabusRequestNOK reqNOK;
  struct JabusAnswerNOK ansNOK;
  struct JabusRequestProbe reqProbe;
  struct JabusAnswerProbe ansProbe;
};
#define JABUS_CMD_CONTROL              0x0012
#define JABUS_CMD_GET_SYS_TICK_MS      0x0014
#define JABUS_CMD_NOK                  0x0002
#define JABUS_CMD_PROBE                0x0000

#endif // include guard