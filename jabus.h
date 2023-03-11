#pragma once
#include "_main.h"
#define JABUS_MAX_PKT_LEN (sizeof(union JabusCommands))

extern struct JabusState js;

void jabus_mainloop_handler();