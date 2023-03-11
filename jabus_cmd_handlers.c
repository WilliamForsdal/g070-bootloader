#include "_main.h"


int jabus_cmd_handler_echo(struct JabusState *state, struct JabusRequestEcho *req)
{
    (void)state;
    (void)req;
    return DSG_ENUM_JABUS_CMD_HANDLER_RET_OK;
}

int jabus_cmd_handler_nok(struct JabusState *state, struct JabusRequestNOK *req)
{
    (void)state;
    (void)req;
    return DSG_ENUM_JABUS_CMD_HANDLER_RET_NOT_IMPLEMENTED;
}

int jabus_cmd_handler_read_mem(struct JabusState *state, struct JabusRequestReadMem *req)
{
    (void)state;
    (void)req;
    return DSG_ENUM_JABUS_CMD_HANDLER_RET_NOT_IMPLEMENTED;
}

int jabus_cmd_handler_probe(struct JabusState *state, struct JabusRequestProbe *req)
{
    (void)req;
    struct JabusAnswerProbe *ans = &state->buf->cmds.ansProbe;
    ans->op_flags = 0xaa;
    return DSG_ENUM_JABUS_CMD_HANDLER_RET_OK;
}

extern uint8_t _extbuf_start[];
extern uint8_t _extbuf_size[];
// _extbuf_start = _ebss;
// _extbuf_size = _sstack - _ebss;

int jabus_cmd_handler_get_extbuf_info(struct JabusState *state, struct JabusRequestGetExtbufInfo *req) {

    (void)req;
    struct JabusAnswerGetExtbufInfo *ans = &state->buf->cmds.ansGetExtbufInfo;
    ans->buf_ptr = (uint32_t)_extbuf_start;
    ans->buf_len = (uint32_t)_extbuf_size;

    return DSG_ENUM_JABUS_CMD_HANDLER_RET_OK;
}