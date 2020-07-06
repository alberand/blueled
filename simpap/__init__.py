from time import sleep
import atexit
import threading
import sys

from simpap.simpap_protocol import *

class SerialTransport:
    
    def __init__(self, port):
        self.ser = serial.Serial(
                port=port,
                baudrate=115200,
                parity=serial.PARITY_NONE,
                stopbits=serial.STOPBITS_ONE,
                bytesize=serial.EIGHTBITS,
                timeout=0.5
        )
        self.ser.isOpen()

    def write(self, data):
        return self.ser.write(data)

    def read(self, size):
        return self.ser.read(size)

    def avaliable(self):
        return self.ser.in_waiting

def exec_cmd(cmd):
    c = cmd[0]
    args = cmd
    print(f'cmd: {c}; args: {args}')
    if s.is_cmd(cmd):
        if args != c:
            a = CMD[c][1]
            b = CMD[c][0]
            s.send(b(a(args)))
        else:
            s.send(CMD[c][0]())

def worker(s):
    t = threading.currentThread()
    while getattr(t, "running", True):
        msg = s.receive()
        if msg:
            print(msg)

        sleep(0.01)

def quit():
    receiver.running = False
    receiver.join()
    serial.ser.close()

# so setup
# serial = SerialTransport('/dev/blueled')
serial = SerialTransport('/dev/ttyUSB0')
# serial = SerialTransport('/tmp/blueledish')
s = Simpap(serial)
# assign functions
send = s.send
cmd = exec_cmd

# start receiving thread
receiver = threading.Thread(target=worker, args=(s,))
receiver.start()
