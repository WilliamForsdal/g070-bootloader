import serial
import time


port = serial.Serial("COM9", 115200)

port.write(b'\xff\xff\x02\x00\xaa\x55')
time.sleep(0.05)
print("0x" + port.read_all().hex())
time.sleep(0.5)
# port.write(b'b')
# time.sleep(0.05)
# print("0x" + port.read_all().hex())
