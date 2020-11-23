import time
import select
import serial
import sys
import binascii
import struct
from pprint import pprint

class Simpap:

    START_COMM = 0xAA
    ACK = 0xBB

    def __init__(self, transport):
        self.buf = b''
        self.transport = transport
        self.busy = False

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
                print(f'FRAME: {self.buf}')
                print("CRC: 0x{:02x} (recv) != 0x{:02x}".format(
                    int.from_bytes(self.buf[-2:], "big"),
                    binascii.crc_hqx(self.buf[:-2], 0xFFFF)))
                self.buf = b''
                return

            self.last_cmd = self.buf[:-2].decode()
            self.buf = b''

            return self.last_cmd

    def receive(self):
        while self.transport.avaliable():
            msg = self.accept(self.transport.read(1))
            if msg:
                return msg

    def expect(self, data, timeout=1000):
        received = bytes()
        part = None
        print(f'[DEBUG] Waiting for {binascii.hexlify(data)}')
        # timeout is in [ms]
        while timeout:
            # print(f'[DEBUG] Already received {binascii.hexlify(received)}')
            if self.transport.avaliable():
                part = self.transport.read(1)

            if part:
                received += part

            if received == data:
                print(f'[DEBUG] Good: Received {binascii.hexlify(data)}')
                return True
            timeout -= 1
            time.sleep(float(timeout)/1000000.0)

        return False

    def send(self, frame):
        if self.busy:
            return
        self.busy = True
        self.write(self.START_COMM.to_bytes(1, byteorder='little'))
        if not self.expect(self.ACK.to_bytes(1, byteorder='little')):
            self.busy = False
            return
        self.write(frame)
        if not self.expect(self.ACK.to_bytes(1, byteorder='little'), 2000):
            self.busy = False
            return
        self.busy = False

    def write(self, data):
        print(f'-> {binascii.hexlify(data)}')
        self.transport.write(data)

    def compose(self, fmt, data=[]):
        print(f'fmt: {fmt}; data: {data}')
        payload = struct.pack(fmt, *data)
        crc = binascii.crc_hqx(payload, 0xFFFF)

        frame = f'~'.encode() + payload + crc.to_bytes(2, byteorder='little') + '~'.encode()

        return frame
