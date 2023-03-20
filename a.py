import serial
import time
from _main import *
import bincopy
import struct


def cmd(pkt, port: serial.Serial, extdata: bytes = None):
    tx(pkt, port, extdata)
    return rx(pkt.header.cmd, port)

def tx(pkt, port: serial.Serial, extdata: bytes = None, num_preambles: int = 1):
    if extdata is not None:
        pkt.header.ext_length = len(extdata)

    data = pkt.pack()
    fcs0, fcs1 = struct.unpack("<HH", data[:4])
    for d in data[4:]:
        fcs0 += d
        fcs1 += fcs0
    fcs0 %= 0xff
    fcs1 %= 0xff
    fcs0 = ~(fcs0) & 0xff
    fcs1 = ~(fcs1) & 0xff
    send = b'\xff'*num_preambles + data + struct.pack("<BB", fcs0, fcs1)
    print(send.hex())
    port.write(send)
    if extdata is None:
        return

    fcs0 = fcs1 = 0
    # tx extdata
    for b in extdata:
        fcs0 += b
        fcs1 += fcs0

    port.write(extdata)

    fcs0 %= 65535
    fcs1 %= 65535
    port.write(struct.pack("<HH", fcs0, fcs1))


def rx(cmd: int, port: serial.Serial):
    tmo = time.time() + .1
    buf = bytes()
    while 1:
        if time.time() > tmo:
            return None

        rx = port.read_all()
        if rx is not None:
            buf += rx

        if len(buf) < 7:
            continue
        if buf[0] != 0xff:
            buf = buf[1:]
            continue
        ans = ans_from_bytes(buf.lstrip(b'\xff'))
        if ans == -1:
            continue
        if ans is not None:
            print(ans)
            return ans


def ans_from_bytes(reply: bytes):
    if not reply:
        return None
    if len(reply) < 6:
        return None
    dst, length, cmd = struct.unpack("<BBH", reply[:4])
    if length > (len(reply) - 2):  # remove fcs
        return -1
    main_pkt = reply[:length+2]
    rx_fcs0, rx_fcs1 = main_pkt[-2:]
    fcs0, fcs1 = struct.unpack("<HH", main_pkt[:4])
    for b in main_pkt[4:-2]:
        fcs0 += b
        fcs1 += fcs0
    fcs0 %= 255
    fcs1 %= 255
    fcs0 = (~fcs0) & 0xff
    fcs1 = (~fcs1) & 0xff
    if fcs0 != rx_fcs0 or fcs1 != rx_fcs1:
        return -1  # bad checksum
    
    ans = JABUS_CMDS_MAP[cmd][1]()
    ans.unpack(reply[:length])
    if cmd & 0x01:  # extended?
        extdata_and_cs = reply[length+2:]
        fcs0 = fcs1 = 0
        extlen = ans.header.ext_length
        if len(extdata_and_cs) != (extlen + 4):
            return None
        for b in extdata_and_cs[:-4]:
            fcs0 += b
            fcs1 += fcs0
        
        fcs0 %= 65535
        fcs1 %= 65535

        (rx_fcs0, rx_fcs1) = struct.unpack("<HH", extdata_and_cs[extlen:])
        if rx_fcs0 != fcs0 or rx_fcs1 != fcs1:
            return None # Bad extended checksum
        ans.ext_data = extdata_and_cs[:-4]
        

    else:
        ans.ext_data = b""
    return ans


def main():
    port = serial.Serial("COM9", 115200)
    ret = tx(JabusRequestReset(reset_mode_magic=ENUM_RESET_MODE.NORMAL_OP_MODE), port)
    return
    ret: JabusAnswerGetExtbufInfo = cmd(JabusRequestGetExtbufInfo(), port)
    if ret is None:
        print("no ans.")
        return
    extdata = bytes([0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15])
    echo_ext = JabusRequestEchoExt()
    echo_ext.header.ext_address = ret.buf_ptr
    ret = cmd(echo_ext, port, extdata)
    print(ret.ext_data.hex())

    settings_info: JabusAnswerGetSettingsInfo = cmd(JabusRequestGetSettingsInfo(), port)
    print(settings_info)

    for i in range(settings_info.num_settings):
        block = cmd(JabusRequestReadSettingsBlock(block_index=i), port)
        print(block.ext_data.hex())

main()
