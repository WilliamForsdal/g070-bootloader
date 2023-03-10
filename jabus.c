#include "jabus.h"
#include "mersienne.h"

union JabusBufferUnion buf;
struct JabusState js = {
    .buf = &buf
};

void handle(uint8_t b)
{
    if(js.got_pkt) {
        // Still waiting to handle current packet in userspace.
        return;
    }

    switch (js.state) {
        // wait for preambles
    case 0:
        if (b == 0xFF) {
            js.state++;
        }
        break;
    case 1: // Consume preambles
        if (b != 0xFF) {
            js.state++;
        }
        break;

    case 2:
        js.buf->data[0] = b;
        js.buf_ptr++;
        js.len_to_rx = b;
        js.fcs1 = js.fcs0 = b;
        js.state++;
        break;

    case 3:
        js.buf->data[js.buf_ptr++] = b;
        js.len_to_rx--;
        js.fcs0 += b;
        js.fcs1 += js.fcs0;
        js.fcs0 = mod255(js.fcs0);
        js.fcs1 = mod255(js.fcs1);
        if (js.len_to_rx == 0) {
            js.state++;
        }
        break;

    case 4:
        if (js.fcs0 != b) {
            js.state = 0; // Bad checksum
        } else {
            js.state++;
        }
        break;

    case 5:
        if (js.fcs1 == b) {
            js.got_pkt = 1;
        }
        // CRC is ok, handle cmd.
        js.state = 0; // Bad checksum

        break;
    default:
        js.state = 0;
        break;
    }
}