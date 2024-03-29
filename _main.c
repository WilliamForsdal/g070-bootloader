// auto generated by dsg2.py, SRC002-103 commit hash 1548f0e7cf347616f872d835d6da2b5632115fc0
// Run with args: ['C:\\dev\\src002-103\\dsg2.py', '_main.dsg', '--gen_h', '--gen_c', '--gen_py']
#include "jabus.h"
#include "_main.h"
const struct Setting_SerialNumbers setting_default_SerialNumbers = { 
    .serialNumbers        = { 0 },       // 0
    .crc32                = 0,           // 64
 }; // size=68, align=4

const struct Setting_SettingsBlock1 setting_default_SettingsBlock1 = { 
    .setting1             = 0xDEADBEEF,  // 0, default=0xDEADBEEF
    .setting2             = 0,           // 4
    .setting3             = 0,           // 8
    .setting4             = 0,           // 12
    .crc32                = 0,           // 16
 }; // size=20, align=4

const struct Setting_SettingsBlock2 setting_default_SettingsBlock2 = { 
    .ching                = 0,           // 0
    .chong                = 0,           // 4
    .__pad01              = {0},         // 6
    .crc32                = 0,           // 8
 }; // size=12, align=4

const void *settings_defaults[] = 
{
    &setting_default_SettingsBlock1,
    &setting_default_SettingsBlock2,
    &setting_default_SerialNumbers,
};

const uint8_t settings_sizes[] = 
{
    sizeof(struct Setting_SettingsBlock1),
    sizeof(struct Setting_SettingsBlock2),
    sizeof(struct Setting_SerialNumbers),
};

// global
struct SettingsMain settings_new;
union SettingsUnionMain settings_union_data;


int jabus_pkt_handler_autogen(uint16_t cmd, struct JabusState *js)
{
    int ret = 0;
    switch (cmd) {
    // handlers come here:
    case JABUS_CMD_ECHO:
        ret = jabus_cmd_handler_echo(js, &js->buf->cmds.reqEcho);
        js->buf->header.length = sizeof(struct JabusAnswerEcho);
        break;
    case JABUS_CMD_ECHO_EXT:
        ret = jabus_cmd_handler_echo_ext(js, &js->buf->cmds.reqEchoExt);
        js->buf->header.length = sizeof(struct JabusAnswerEchoExt);
        break;
    case JABUS_CMD_GET_EXTBUF_INFO:
        ret = jabus_cmd_handler_get_extbuf_info(js, &js->buf->cmds.reqGetExtbufInfo);
        js->buf->header.length = sizeof(struct JabusAnswerGetExtbufInfo);
        break;
    case JABUS_CMD_GET_FUNC_PTR:
        ret = jabus_cmd_handler_get_func_ptr(js, &js->buf->cmds.reqGetFuncPtr);
        js->buf->header.length = sizeof(struct JabusAnswerGetFuncPtr);
        break;
    case JABUS_CMD_GET_SETTINGS_INFO:
        ret = jabus_cmd_handler_get_settings_info(js, &js->buf->cmds.reqGetSettingsInfo);
        js->buf->header.length = sizeof(struct JabusAnswerGetSettingsInfo);
        break;
    case JABUS_CMD_JUMP_TO_MEM:
        ret = jabus_cmd_handler_jump_to_mem(js, &js->buf->cmds.reqJumpToMem);
        js->buf->header.length = sizeof(struct JabusAnswerJumpToMem);
        break;
    case JABUS_CMD_NOK:
        ret = jabus_cmd_handler_nok(js, &js->buf->cmds.reqNOK);
        js->buf->header.length = sizeof(struct JabusAnswerNOK);
        break;
    case JABUS_CMD_READ_MEM:
        ret = jabus_cmd_handler_read_mem(js, &js->buf->cmds.reqReadMem);
        js->buf->header.length = sizeof(struct JabusAnswerReadMem);
        break;
    case JABUS_CMD_READ_SETTINGS_BLOCK:
        ret = jabus_cmd_handler_read_settings_block(js, &js->buf->cmds.reqReadSettingsBlock);
        js->buf->header.length = sizeof(struct JabusAnswerReadSettingsBlock);
        break;
    case JABUS_CMD_RESET:
        ret = jabus_cmd_handler_reset(js, &js->buf->cmds.reqReset);
        js->buf->header.length = sizeof(struct JabusAnswerReset);
        break;
    case JABUS_CMD_WRITE_MEM:
        ret = jabus_cmd_handler_write_mem(js, &js->buf->cmds.reqWriteMem);
        js->buf->header.length = sizeof(struct JabusAnswerWriteMem);
        break;
    case JABUS_CMD_GET_LINKER_SYMBOLS:
        ret = jabus_cmd_handler_get_linker_symbols(js, &js->buf->cmds.reqGetLinkerSymbols);
        js->buf->header.length = sizeof(struct JabusAnswerGetLinkerSymbols);
        break;
    case JABUS_CMD_PROBE:
        ret = jabus_cmd_handler_probe(js, &js->buf->cmds.reqProbe);
        js->buf->header.length = sizeof(struct JabusAnswerProbe);
        break;

    default:
        ret = -100; // unknown cmd.
        break;
    }
    return ret;
}
