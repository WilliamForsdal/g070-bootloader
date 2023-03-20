#include "jabus.h"
#include "board.h"
#include "mersienne.h"
#include "uart1.h"

#ifndef NULL
#define NULL 0
#endif

union JabusBufferUnion buf;
struct JabusState js = {.buf = &buf, .state = 0};

void handle(uint8_t b)
{
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
            if ((js.buf->header.cmd & 1) == 0) {
                js.state = JABUS_STATE_GOT_PACKET;
            } else {
                // Also rx extended data
                js.fcs0 = js.fcs1 = 0;
                js.fletcher_count = 360 - 4;
                if (js.buf->header_req_ext.ext_address) {
                    js.ext_ptr = (uint8_t *)js.buf->header_req_ext.ext_address;
                } else {
                    js.ext_ptr = NULL;
                }
                js.ext_down_count = js.buf->header_req_ext.ext_length; // note that ext_length is at the same position for both requests and answers.
                js.state++;
            }
        }
        break;

    case 5:
        if (js.ext_ptr) { // ptr might be NULL if we couldn't allocate mem.
            *js.ext_ptr++ = b;
        }
        js.fcs0 += b;
        js.fcs1 += js.fcs0;
        if (js.fletcher_count-- == 0) {
            js.fcs0 = mod65535(js.fcs0);
            js.fcs1 = mod65535(js.fcs1);
            js.fletcher_count = 360 - 4;
        }
        js.ext_down_count--;
        if (js.ext_down_count == 0) {
            js.fletcher_count = 4; // ??
            js.ext_ptr = js.fcs32_tmp.u8;
            js.state++;
        }
        break;

    case 6:
        *js.ext_ptr++ = b;
        js.fletcher_count--;
        if (js.fletcher_count == 0) {
            js.state = JABUS_STATE_GOT_PACKET;
        }
        break;

    case JABUS_STATE_GOT_PACKET:
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

int send_jabus_ans()
{
    // TODO check cmd-id is known and valid.
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
    if ((js.buf->header.cmd & 1) > 0) {
        js.fcs0 = js.fcs1 = 0;
        js.fletcher_count = 360 - 4;
        // Send extended data
        while (js.ext_down_count--) {
            uint8_t b = *js.ext_ptr++;
            uart_tx_blocking(b);
            js.fcs0 += b;
            js.fcs1 += js.fcs0;
            js.fletcher_count--;
            if (js.fletcher_count) {
                continue;
            }
            js.fcs0 = mod65535(js.fcs0);
            js.fcs1 = mod65535(js.fcs1);
            js.fletcher_count = 360 - 4;
        }
        js.fcs0 = mod65535(js.fcs0);
        js.fcs1 = mod65535(js.fcs1);
        uint32_t fcs_final = (js.fcs0 | (js.fcs1 << 16));
        tx_blocking(((uint8_t *)(&fcs_final)), 4);
    }
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
    if (js.state == JABUS_STATE_GOT_PACKET) {
        if ((buf.header.cmd & 1) > 0) {
            // Extended data, verify checksum.
            js.fcs0 = mod65535(js.fcs0);
            js.fcs1 = mod65535(js.fcs1);
            uint32_t rx_fcs = js.fcs32_tmp.u32;
            uint32_t calc_fcs = js.fcs1 << 16 | js.fcs0;

            if (calc_fcs != rx_fcs) {
                // bad checksum!
                send_nok(DSG_ENUM_JABUS_CMD_HANDLER_RET_NOK_EXTDATA_FCS);
                js.state = 0; // mark that we're ready to handle next msg
                return;
            }
        }
        uint16_t cmd = buf.header.cmd & (~((uint16_t)1));
        js.fletcher_count = 0; // In case it's not 0 before we call handler, set it to zero.
        int ret = jabus_pkt_handler_autogen(cmd, &js);
        if (ret < 0) {
            send_nok(ret);
        } else {
            if (js.fletcher_count != 0) {
                js.buf->header_ans_ext.cmd |= 1; // also tx extdata.
            }
            send_jabus_ans();
        }
        js.state = 0;
    }
}

void uart_rx_handler(uint8_t b) { handle(b); }
