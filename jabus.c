#include "jabus.h"
#include "mersienne.h"
#include "uart1.h"

union JabusBufferUnion buf;
struct JabusState js = {.buf = &buf, .state = 0};

void handle(uint8_t b)
{
    if (js.got_pkt) {
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
            js.buf->header.dst = b;
            js.got_len = 1;
            js.state++;
        }
        break;

    case 2:
        js.buf->data[js.got_len++] = b;
        if (js.got_len == sizeof(struct JabusHeader)) {
            if (js.buf->header.length > JABUS_MAX_PKT_LEN) {
                // cannot fit in buffer!
                js.state = 0;
            } else {
                // got valid header:
                js.fcs0 = js.buf->u16header[0];
                js.fcs1 = js.buf->u16header[1];
                // no need to initialize fletcher_count, as max msg len is 127, so c0/c1 will never overflow.
                js.state++;
            }
        }
        break;

    case 3:
        if (js.got_len == (js.buf->header.length)) {
            // got full packet data and FCS, so this is the first fcs byte:
            js.buf->data[js.got_len++] = b;
            js.state++;
        } else {
            js.buf->data[js.got_len++] = b;
            js.fcs0 += b; // fletcher algo
            js.fcs1 += js.fcs0;
        }
        break;

    case 4:                           // rx checksum
        js.buf->data[js.got_len] = b; // Last fcs byte
        if ((mod255(js.fcs0) ^ 0xff) != (js.buf->data[js.got_len - 1]) || (mod255(js.fcs1) ^ 0xff) != b) {
            uart_tx(0xfe);
            uart_tx(0xfe);
            js.state = 0; // Bad checksum
        } else {
            js.got_pkt = 1;
            js.state = 0; // Bad checksum
        }
        break;

    default:
        js.state = 0;
        break;
    }
}

void tx_blocking(uint8_t *data, int len)
{
    while (len--) {
        uint8_t b = *data++;
        while (uart_tx(b) < 0) {
        }
    }
}

void send_jabus_ans()
{
    js.fcs0 = buf.u16header[0];
    js.fcs1 = buf.u16header[1];
    int tx_count = buf.header.length + 2; // Also send FCS
    int fcs_count = buf.header.length - sizeof(struct JabusHeader);
    if (fcs_count) {
        uint8_t *fcs_ptr = buf.data + sizeof(struct JabusHeader);
        while (fcs_count--) {
            uint8_t b = *fcs_ptr++;
            // fletcher algo
            js.fcs0 += b;
            js.fcs1 += js.fcs0;
        }
    }
    buf.data[buf.header.length] = mod255(js.fcs0) ^ 0xff;
    buf.data[buf.header.length + 1] = mod255(js.fcs1) ^ 0xff;
    uart_tx(0xff);
    tx_blocking(buf.data, tx_count);
}

static void send_nok(int errorCode)
{
    buf.cmds.ansNOK.the_bad_cmd = buf.header.cmd;
    buf.cmds.ansNOK.error_code = errorCode;
    buf.cmds.ansNOK.header.cmd = JABUS_CMD_NOK;
    buf.cmds.ansNOK.header.length = sizeof(struct JabusAnswerNOK);
    buf.cmds.ansNOK.header.dst = 0;
    send_jabus_ans();
}

void jabus_mainloop_handler()
{
    if (js.got_pkt) {
        uint16_t cmd = buf.header.cmd & (~((uint16_t)1));
        int ret = jabus_pkt_handler_autogen(cmd, &js);
        if(ret < 0) {
            send_nok(ret);
        }
        else {
            send_jabus_ans();
        }
        js.got_pkt = 0;
    }
}

void uart_rx_handler(uint8_t b) { handle(b); }
