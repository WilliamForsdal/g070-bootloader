import serial
import time


port = serial.Serial("COM9", 115200)

port.write(b'\xfe\xfe')

time.sleep(0.1)
print("0x" + port.read_all().hex())

