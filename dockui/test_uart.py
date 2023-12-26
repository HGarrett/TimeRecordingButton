import serial
import time
from datetime import datetime

EEPROM_SIZE = 0x7F

with serial.Serial('COM10', baudrate=646, timeout=5) as ser:
    ser.write(b'd')
    time.sleep(0.1)
    x = ser.read()
    print(x)

    # print("\nreset and calibrate")
    # print(datetime.utcfromtimestamp(time.time()).strftime('%Y-%m-%d %H:%M:%S'))
    # ser.write(b'c')
    # time.sleep(0.1)
    # x = ser.read()
    # print(x.hex())
    # x = ser.read()
    # print(x.hex())
    # x = ser.read()
    # print(x)

    print("\ntest time stamp")
    print(datetime.utcfromtimestamp(time.time()).strftime('%Y-%m-%d %H:%M:%S'))
    ser.write(b'w')
    time.sleep(0.1)
    x = ser.read()
    print(x.hex())
    x = ser.read()
    print(x.hex())
    x = ser.read()
    print(x)

    time.sleep(5)

    print("\ntest time stamp")
    print(datetime.utcfromtimestamp(time.time()).strftime('%Y-%m-%d %H:%M:%S'))
    ser.write(b'w')
    time.sleep(0.1)
    x = ser.read()
    print(x.hex())
    x = ser.read()
    print(x.hex())
    x = ser.read()
    print(x)

    time.sleep(9)

    print("\ntest time stamp")
    print(datetime.utcfromtimestamp(time.time()).strftime('%Y-%m-%d %H:%M:%S'))
    ser.write(b'w')
    time.sleep(0.1)
    x = ser.read()
    print(x.hex())
    x = ser.read()
    print(x.hex())
    x = ser.read()
    print(x)

    # print("\ntransfer")
    # ser.write(b't')
    # time.sleep(0.1)
    # eeprom = []
    # for add in range(0, EEPROM_SIZE+1):
    #     eeprom.append(ser.read().hex())
    # print(eeprom)
    # x = ser.read()
    # print(x)