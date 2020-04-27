import time
import serial
import binascii

def crc_16(msg):
    poly = 0x8408
    crc = 0xffff
    for byte in msg:
        for _ in range(8):
            if (byte ^ crc) & 1:
                crc = (crc >> 1) ^ poly
            else:
                crc >>= 1
            byte >>= 1
    return crc ^ 0xffff

class Simpap:
    def __init__(self):
        pass

def form_frame(data):
    crc = binascii.crc_hqx(data, 0xFFFF)

    s = f'~'.encode() + data + crc.to_bytes(2, byteorder='big') + '~'.encode()
    return s

def cmd_solid_color(color):
    cmd = 0x0041
    data = cmd.to_bytes(2, byteorder='big') + color.to_bytes(4, byteorder='big')
    return data

def cmd_gradient_two():
    # 0B 03 00FF0000 0000FF00 000000FF
    data = 0x042.to_bytes(2, byteorder='big') 
    data += 0x02.to_bytes(1, byteorder='big')
    data += 0x00FF00.to_bytes(4, byteorder='big')
    data += 0x0000FF.to_bytes(4, byteorder='big')

    return data

def cmd_gradient_three():
    # 0B 03 00FF0000 0000FF00 000000FF
    data = 0x042.to_bytes(2, byteorder='big') 
    data += 0x03.to_bytes(1, byteorder='big')
    data += 0x00FF00.to_bytes(4, byteorder='big')
    data += 0xFF0000.to_bytes(4, byteorder='big')
    data += 0x0000FF.to_bytes(4, byteorder='big')

    return data

def cmd_cylon():
    cmd = 0x0043
    data = cmd.to_bytes(2, byteorder='big')
    return data

def cmd_rainbow():
    cmd = 0x0044
    data = cmd.to_bytes(2, byteorder='big')
    return data

def cmd_stroboscope():
    cmd = 0x0045
    data = cmd.to_bytes(2, byteorder='big')
    return data

def cmd_confetti():
    cmd = 0x0046
    data = cmd.to_bytes(2, byteorder='big')
    return data

def cmd_sinelon():
    cmd = 0x0047
    data = cmd.to_bytes(2, byteorder='big')
    return data

def cmd_bpm():
    cmd = 0x0048
    data = cmd.to_bytes(2, byteorder='big')
    return data

def cmd_juggle():
    cmd = 0x0049
    data = cmd.to_bytes(2, byteorder='big')
    return data

def cmd_fadeinout():
    cmd = 0x004a
    data = cmd.to_bytes(2, byteorder='big')
    return data

def cmd_twinkle():
    cmd = 0x004b
    data = cmd.to_bytes(2, byteorder='big')
    return data

def cmd_snowsparkle():
    cmd = 0x004c
    data = cmd.to_bytes(2, byteorder='big')
    return data

if __name__ == '__main__':

    ser = serial.Serial(
            port='/dev/blueled',
            baudrate=115200,
            parity=serial.PARITY_NONE,
            stopbits=serial.STOPBITS_ONE,
            bytesize=serial.EIGHTBITS
    )

    ser.isOpen()

    i = 0
    while True:
        tosend = input('> ')

        if tosend[0] == 's':
            tosend = cmd_solid_color(int(tosend[1:], 16))
        if tosend[0] == 'g' and tosend[1] == '2':
            tosend = cmd_gradient_two()
        if tosend[0] == 'g' and tosend[1] == '3':
            tosend = cmd_gradient_three()
        if tosend[0] == 'c':
            tosend = cmd_cylon()
        if tosend[0] == 'r':
            tosend = cmd_rainbow()
        if tosend[0] == 'd':
            tosend = cmd_stroboscope()
        if tosend[0] == 'f':
            tosend = cmd_confetti()
        if tosend[0] == 'i':
            tosend = cmd_sinelon()
        if tosend[0] == 'b':
            tosend = cmd_bpm()
        if tosend[0] == 'j':
            tosend = cmd_juggle()
        if tosend[0] == 'o':
            tosend = cmd_fadeinout()
        if tosend[0] == 't':
            tosend = cmd_twinkle()
        if tosend[0] == 'p':
            tosend = cmd_snowsparkle()

        ff = form_frame(tosend)
        print(f'-> {binascii.hexlify(ff)}')
        ser.write(ff)

        time.sleep(0.1)

        response = ''
        while ser.inWaiting() > 0:
            response += ser.read(1).decode()
        if response:
            print(f' <- {response}')
