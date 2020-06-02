from time import sleep
import atexit
import threading

from simpap.simpap_protocol import *

class SerialTransport:
    
    def __init__(self, port):
        self.ser = serial.Serial(
                port=port,
                baudrate=115200,
                parity=serial.PARITY_NONE,
                stopbits=serial.STOPBITS_ONE,
                bytesize=serial.EIGHTBITS
        )
        self.ser.isOpen()

    def write(self, data):
        return self.ser.write(data)

    def read(self, size):
        return self.ser.read(size)

    def avaliable(self):
        return self.ser.in_waiting

serial = SerialTransport('/dev/blueled')
s = Simpap(serial)
send = s.send

running = True

def worker():
    while running:
        msg = s.receive()
        if msg:
            print(msg)

        sleep(0.01)

def quit():
    running = False
    serial.ser.close()

receiver = threading.Thread(target=worker)
receiver.start()

atexit.register(quit)
