import serial
import time
from _main import *
import bincopy
import struct


def cmd(pkt, port: serial.Serial, num_preambles: int = 1):
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
    return rx(pkt.header.cmd, port)


def rx(cmd: int, port: serial.Serial):
    tmo = time.time() + .1
    buf = bytes()
    while 1:
        if time.time() > tmo:
            return None
        
        rx = port.read_all()
        if rx is None:
            continue
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
            return ans

def ans_from_bytes(reply: bytes):
    if not reply:
        return None
    if len(reply) < 6:
        return None
    dst, length, cmd = struct.unpack("<BBH", reply[:4])
    if length != len(reply) - 2:  # remove fcs
        return -1
    data = reply[4:-2]
    rx_fcs0, rx_fcs1 = reply[-2:]
    fcs0, fcs1 = struct.unpack("<HH", reply[:4])
    for b in data:
        fcs0 += b
        fcs1 += fcs0
    fcs0 %= 255
    fcs1 %= 255
    fcs0 = (~fcs0) & 0xff
    fcs1 = (~fcs1) & 0xff
    if fcs0 != rx_fcs0 or fcs1 != rx_fcs1:
        return -1 # bad checksum
    ans = JABUS_CMDS_MAP[cmd][1]()
    ans.unpack(reply[:-2])
    if cmd & 0x01:  # extended?
        raise Exception("Extended data not implemented.")
    else:
        ans.ext_data = b""
    return ans

def main():
    port = serial.Serial("COM9", 115200)
    probe = JabusRequestProbe()
    probe.header.dst = 1
    ret = cmd(probe, port)
    if ret is None:
        print("no ans.")
        return
    print(ret)

    extbuf = JabusAnswerGetExtbufInfo()
    ret = cmd(extbuf, port)
    
    if ret is None:
        print("no ans.")
        return
    print(ret)

main()