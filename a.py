import serial
import time


port = serial.Serial("COM9", 115200)

port.write(b'P')
