#!/usr/bin/env python3
import serial
import sys
import platform
import glob

if platform.system() == "Darwin":
    devices = glob.glob("/dev/tty.usbserial*")
    if not devices:
        print("No tty.usbserial devices found.")
        sys.exit(1)
    dev = serial.Serial(devices[0], 38400)
else:
    dev = serial.Serial("/dev/ttyUSB0", 38400)

print("> Returned data:", file=sys.stderr)

while True:
    x = dev.read()
    sys.stdout.buffer.write(x)
    sys.stdout.flush()
