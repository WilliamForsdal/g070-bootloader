#pragma once 
#include "main.h"
#include "jabus_basic.h"

union PACKED JabusBufferUnion {
    struct PACKED JabusHeader header;
    struct PACKED JabusHeaderReqExtended header_req_ext;
    struct PACKED JabusHeaderAnsExtended header_ans_ext;
    union JabusCommands cmds;
    uint8_t data[sizeof(union JabusCommands)];
    uint16_t u16header[2]; // for fletcher, we want to initialize c0/c1 with header data.
};

struct JabusState {
    int state;
    int buf_ptr;
    int len_to_rx;
    int got_pkt;
    union JabusBufferUnion *buf;
    uint16_t fcs0;
    uint16_t fcs1;
};

extern struct JabusState js;