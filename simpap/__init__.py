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

class Communication:

    def __init__(self, port):
        self.serial = SerialTransport(port)
        self.app_layer = Simpap(self.serial)
    
        self.receiver = threading.Thread(target=self.worker, args=(self.app_layer,))
        self.receiver.start()

    def cmd(self, cmd):
        c = cmd[0]
        args = cmd
        print(f'cmd: {c}; args: {args}')
        if self.app_layer.is_cmd(cmd):
            if args != c:
                a = CMD[c][1]
                b = CMD[c][0]
                self.app_layer.send(b(a(args)))
            else:
                self.app_layer.send(CMD[c][0]())

    def worker(self, app_layer):
        t = threading.currentThread()
        while getattr(t, "running", True):
            msg = app_layer.receive()
            if msg:
                print(msg)
    
            sleep(0.01)
    
    def stop(self):
        self.receiver.running = False
        self.receiver.join()
        self.serial.ser.close()
