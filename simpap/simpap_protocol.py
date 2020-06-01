import time
import select
import serial
import sys
import binascii
from pprint import pprint

def cmd_set_leds_number(*args):
    cmd = 0x0020
    data = cmd.to_bytes(2, byteorder='big') + args[0].to_bytes(2, byteorder='big')
    return data

def cmd_solid_color(*args):
    cmd = 0x0041
    data = cmd.to_bytes(2, byteorder='big') + args[0].to_bytes(4, byteorder='big')
    return data

def cmd_gradient_two(*args):
    # 0B 03 00FF0000 0000FF00 000000FF
    data = 0x042.to_bytes(2, byteorder='big') 
    data += 0x02.to_bytes(1, byteorder='big')
    data += 0x00FF00.to_bytes(4, byteorder='big')
    data += 0x0000FF.to_bytes(4, byteorder='big')

    return data

def cmd_gradient(*args):
    # 0B 03 00FF0000 0000FF00 000000FF
    data = 0x042.to_bytes(2, byteorder='big') 
    data += 0x03.to_bytes(1, byteorder='big')
    data += 0x00FF00.to_bytes(4, byteorder='big')
    data += 0xFF0000.to_bytes(4, byteorder='big')
    data += 0x0000FF.to_bytes(4, byteorder='big')

    return data

def cmd_cylon(*args):
    cmd = 0x0043
    data = cmd.to_bytes(2, byteorder='big')
    return data

def cmd_rainbow(*args):
    cmd = 0x0044
    data = cmd.to_bytes(2, byteorder='big')
    return data

def cmd_stroboscope(*args):
    cmd = 0x0045
    data = cmd.to_bytes(2, byteorder='big')
    return data

def cmd_confetti(*args):
    cmd = 0x0046
    data = cmd.to_bytes(2, byteorder='big')
    return data

def cmd_sinelon(*args):
    cmd = 0x0047
    data = cmd.to_bytes(2, byteorder='big')
    return data

def cmd_bpm(*args):
    cmd = 0x0048
    data = cmd.to_bytes(2, byteorder='big')
    return data

def cmd_juggle(*args):
    cmd = 0x0049
    data = cmd.to_bytes(2, byteorder='big')
    return data

def cmd_fadeinout(*args):
    cmd = 0x004a
    data = cmd.to_bytes(2, byteorder='big')
    return data

def cmd_twinkle(*args):
    cmd = 0x004b
    data = cmd.to_bytes(2, byteorder='big')
    return data

def cmd_snowsparkle(*args):
    cmd = 0x004c
    data = cmd.to_bytes(2, byteorder='big')
    return data

def cmd_train(*args):
    cmd = 0x004d
    data = cmd.to_bytes(2, byteorder='big')
    return data

def cmd_help(*args):
    pprint(CMD)
    return cmd_rainbow()

CMD = {
        'l': [cmd_set_leds_number, lambda x: int(x[1:])],
        's': [cmd_solid_color, lambda x: int(x[1:], 16)],
        'g': [cmd_gradient, lambda x: int(x)],
        'c': [cmd_cylon, lambda x: int(x)],
        'r': [cmd_rainbow, lambda x: int(x)],
        'd': [cmd_stroboscope, lambda x: int(x)],
        'f': [cmd_confetti, lambda x: int(x)],
        'i': [cmd_sinelon, lambda x: int(x)],
        'b': [cmd_bpm, lambda x: int(x)],
        'j': [cmd_juggle, lambda x: int(x)],
        'o': [cmd_fadeinout, lambda x: int(x)],
        't': [cmd_twinkle, lambda x: int(x)],
        'p': [cmd_snowsparkle, lambda x: int(x)],
        'a': [cmd_train, lambda x: int(x)],
        'h': [cmd_help, lambda x: int(x)],
}

class Simpap:
    def __init__(self, port):
        self.buf = b''
        self.ser = serial.Serial(
                port=port,
                baudrate=115200,
                parity=serial.PARITY_NONE,
                stopbits=serial.STOPBITS_ONE,
                bytesize=serial.EIGHTBITS
        )

        self.ser.isOpen()

        # parser state
        self.started = False
        self.finished = False

        # last received message
        self.msg_last = ''

    def accept(self, char):
        if char == b'~' and not self.started:
            self.started = True
            self.finished = False
            return

        if char != b'~':
            self.buf += char
            return

        if char == b'~' and not self.finished:
            self.finished = True
            self.started = False

            if int.from_bytes(self.buf[-2:], "big") != binascii.crc_hqx(self.buf[:-2], 0xFFFF):
                print('CRC16 of received frame is incorect')

            self.last_cmd = self.buf[:-2].decode()
            self.buf = b''

            return self.last_cmd

    def send(self, data):
        frame = self.compose(data)
        print(f'-> {binascii.hexlify(frame)}')
        self.ser.write(frame)

    def compose(self, data):
        crc = binascii.crc_hqx(data, 0xFFFF)

        frame = f'~'.encode() + data + crc.to_bytes(2, byteorder='big') + '~'.encode()

        return frame

    def is_cmd(self, data):
        if not data:
            return False

        return data[0] in CMD.keys()
