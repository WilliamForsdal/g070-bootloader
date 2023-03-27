#include "_main.h"
#include "main.h"
#include "settings/settings.h"
#include <string.h>

int jabus_cmd_handler_echo(struct JabusState *state, struct JabusRequestEcho *req)
{
    (void)state;
    (void)req;
    return DSG_ENUM_JABUS_CMD_HANDLER_RET_OK;
}

int jabus_cmd_handler_echo_ext(struct JabusState *state, struct JabusRequestEchoExt *req)
{
    state->ext_ptr = (uint8_t *)req->header.ext_address;
    state->ext_down_count = req->header.ext_length;
    return DSG_ENUM_JABUS_CMD_HANDLER_RET_OK;
}

int jabus_cmd_handler_nok(struct JabusState *state, struct JabusRequestNOK *req)
{
    (void)state;
    (void)req;
    return DSG_ENUM_JABUS_CMD_HANDLER_RET_OK;
}

int jabus_cmd_handler_read_mem(struct JabusState *state, struct JabusRequestReadMem *req)
{
    (void)state;
    (void)req;
    return DSG_ENUM_JABUS_CMD_HANDLER_RET_OK;
}

int jabus_cmd_handler_probe(struct JabusState *state, struct JabusRequestProbe *req)
{
    (void)req;
    struct JabusAnswerProbe *ans = &state->buf->cmds.ansProbe;
    ans->op_flags = 0xaa;
    return DSG_ENUM_JABUS_CMD_HANDLER_RET_OK;
}

// _extbuf_start = _ebss;
// _extbuf_size = _sstack - _ebss;

int jabus_cmd_handler_get_extbuf_info(struct JabusState *state, struct JabusRequestGetExtbufInfo *req)
{

    (void)req;
    struct JabusAnswerGetExtbufInfo *ans = &state->buf->cmds.ansGetExtbufInfo;
    ans->buf_ptr = (uint32_t)linkerSymbols.extbuf_start;
    ans->buf_len = linkerSymbols.extbuf_end - linkerSymbols.extbuf_start;

    return DSG_ENUM_JABUS_CMD_HANDLER_RET_OK;
}

int jabus_cmd_handler_get_settings_info(struct JabusState *state, struct JabusRequestGetSettingsInfo *req)
{
    (void)req;
    struct JabusAnswerGetSettingsInfo *ans = &state->buf->cmds.ansGetSettingsInfo;
    ans->num_settings = SETTINGS_COLLECTION_MAIN_NUM_BLOCKS;
    return DSG_ENUM_JABUS_CMD_HANDLER_RET_OK;
}

int jabus_cmd_handler_read_settings_block(struct JabusState *state, struct JabusRequestReadSettingsBlock *req)
{
    if (req->block_index >= SETTINGS_COLLECTION_MAIN_NUM_BLOCKS) {
        return DSG_ENUM_JABUS_CMD_HANDLER_RET_NOK;
    }
    struct JabusAnswerReadSettingsBlock *ans = &state->buf->cmds.ansReadSettingsBlock;
    settings_copy_to_union(req->block_index);
    state->ext_ptr = (uint8_t *)&settings_union_data;
    state->ext_down_count = settings_sizes[req->block_index];
    ans->block_index = req->block_index;
    return DSG_ENUM_JABUS_CMD_HANDLER_RET_OK;
}

int jabus_cmd_handler_reset(struct JabusState *state, struct JabusRequestReset *req)
{
    (void)state;
    if (req->reset_mode_magic != DSG_ENUM_RESET_MODE_NORMAL_OP_MODE && req->reset_mode_magic != DSG_ENUM_RESET_MODE_BOOTLOADER_MODE) {
        return DSG_ENUM_JABUS_CMD_HANDLER_RET_NOK; // Bad mode
    }
    system_reset(req->reset_mode_magic);
    //  This line will never run, we reset CPU above.
    return DSG_ENUM_JABUS_CMD_HANDLER_RET_NOK;
}

int jabus_cmd_handler_write_mem(struct JabusState *state, struct JabusRequestWriteMem *req)
{
    (void)state;
    (void)req;
    return DSG_ENUM_JABUS_CMD_HANDLER_RET_NOT_IMPLEMENTED;
}

int jabus_cmd_handler_get_linker_symbols(struct JabusState *state, struct JabusRequestGetLinkerSymbols *req)
{
    (void)req;
    struct JabusAnswerGetLinkerSymbols *ans = &state->buf->cmds.ansGetLinkerSymbols;
    memcpy(&ans->linker_symbols, &linkerSymbols, sizeof(linkerSymbols));
    return DSG_ENUM_JABUS_CMD_HANDLER_RET_OK;
}

int add(int a, int b) { return a + b; }

int jabus_cmd_handler_jump_to_mem(struct JabusState *state, struct JabusRequestJumpToMem *req)
{
    (void)req;
    int (*fptr_add)(int, int) = (int (*)(int, int))(req->addr);
    int result = fptr_add(req->arg0, req->arg1);
    state->buf->cmds.ansJumpToMem.result = result;
    return DSG_ENUM_JABUS_CMD_HANDLER_RET_OK;
}

int jabus_cmd_handler_get_func_ptr(struct JabusState* state, struct JabusRequestGetFuncPtr *req) {
    
    (void)req;
    uint32_t add_addr = (uint32_t)(&add);
    state->buf->cmds.ansGetFuncPtr.func = add_addr;
    return DSG_ENUM_JABUS_CMD_HANDLER_RET_OK;
}