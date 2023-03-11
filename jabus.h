#pragma once
#include "_main.h"
#define JABUS_MAX_PKT_LEN (sizeof(union JabusCommands))

#define JABUS_CMD_HANDLER_RET_OK  0
#define JABUS_CMD_HANDLER_RET_NOK -1

extern struct JabusState js;

void jabus_mainloop_handler();