#include "_main.h"
#include "jabus.h"
// int jabus_cmd_handler_echo(struct JabusState* state, struct JabusRequestEcho *req);
// int jabus_cmd_handler_nok(struct JabusState* state, struct JabusRequestNOK *req);
// int jabus_cmd_handler_readmem(struct JabusState* state, struct JabusRequestReadMem *req);
// int jabus_cmd_handler_probe(struct JabusState* state, struct JabusRequestProbe *req);

int jabus_cmd_handler_probe(struct JabusState* state, struct JabusRequestProbe *req_probe) { 
    (void)req_probe;
    struct JabusAnswerProbe *ans = &state->buf->cmds.ansProbe;
    ans->op_flags = 0xaa;
    return JABUS_CMD_HANDLER_RET_OK; 
}