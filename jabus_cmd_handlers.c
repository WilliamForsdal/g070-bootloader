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

int jabus_cmd_handler_readmem(struct JabusState *state, struct JabusRequestReadMem *req)
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

int jabus_cmd_handler_fuck(struct JabusState* state, struct JabusRequestFuck *req)
{
    state->buf->cmds.ansFuck.data = ~req->data;
    return DSG_ENUM_JABUS_CMD_HANDLER_RET_OK;
}