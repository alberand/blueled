from time import sleep
import atexit
import threading
import sys

from simpap.simpap_protocol import *

class SerialTransport:
    
    def __init__(self, port):
        self.ser = serial.Serial(
                port=port,
                baudrate=9600,
                parity=serial.PARITY_EVEN,
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
        try:
            self.serial = SerialTransport(port)
        except serial.SerialException:
            print(f'Could not open the {port}')
            return
        self.app_layer = Simpap(self.serial)
    
        self.receiver = threading.Thread(target=self.worker, args=(self.app_layer,))
        self.receiver.setDaemon(True)
        self.receiver.start()

        atexit.register(self.stop)

    def cmd(self, cmd):
        c = cmd[0]
        args = cmd

        try:
            if self.app_layer.is_cmd(cmd):
                if args != c:
                    a = CMD[c][1]
                    b = CMD[c][0]
                    self.app_layer.send(b(a(args)))
                else:
                    self.app_layer.send(CMD[c][0]())
        except serial.SerialException:
            print(f'Could not send command "{cmd}"')
            self.stop()

    def send_raw(self, data):
        self.serial.write(data)

    def worker(self, app_layer):
        t = threading.currentThread()
        while getattr(t, "running", True):
            try:
                if not app_layer.busy:
                    msg = app_layer.receive()
                    if msg:
                        print(msg)
            except OSError:
                print('Failed to read from the port (possibly closed)')
                break
    
            sleep(0.01)
    
    def stop(self):
        self.receiver.running = False
        self.receiver.join()
        self.serial.ser.close()
