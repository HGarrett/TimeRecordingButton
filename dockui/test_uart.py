import serial
import time

EEPROM_SIZE = 0x7F

with serial.Serial('COM10', baudrate=646, timeout=10) as ser:
    ser.write(b'd')
    time.sleep(0.1)
    x = ser.read()
    print(x)

    # print("\nreset and calibrate")
    # ser.write(b'c')
    # time.sleep(0.1)
    # x = ser.read()
    # print(x.hex())
    # x = ser.read()
    # print(x.hex())
    # x = ser.read()
    # print(x)

    # print("\ntest time stamp")
    # ser.write(b'w')
    # time.sleep(0.1)
    # x = ser.read()
    # print(x.hex())
    # x = ser.read()
    # print(x.hex())
    # x = ser.read()
    # print(x)

    # print("\ntest time stamp")
    # ser.write(b'w')
    # time.sleep(0.1)
    # x = ser.read()
    # print(x.hex())
    # x = ser.read()
    # print(x.hex())
    # x = ser.read()
    # print(x)

    # print("\ntest time stamp")
    # ser.write(b'w')
    # time.sleep(0.1)
    # x = ser.read()
    # print(x.hex())
    # x = ser.read()
    # print(x.hex())
    # x = ser.read()
    # print(x)

    print("\ntransfer")
    ser.write(b't')
    time.sleep(0.1)

    eeprom = []
    for add in range(0, EEPROM_SIZE+1):
        eeprom.append(ser.read().hex())
        
    print(eeprom)

    x = ser.read()
    print(x)