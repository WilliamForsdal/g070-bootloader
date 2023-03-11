#pragma once
#include "_main.h"
#define JABUS_MAX_PKT_LEN (sizeof(union JabusCommands))
#define JABUS_STATE_GOT_PACKET 100

extern struct JabusState js;

void jabus_mainloop_handler();