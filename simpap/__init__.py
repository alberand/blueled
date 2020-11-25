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

class Blueled:
    metadata = {
            'set_leds': {'id': 0x20, 'params_num': 1, 'fmt':'<HbI'}, 
            'set_brightness': {'id': 0x21, 'params_num': 1, 'fmt':'<HbI'}, 
            'solid': {'id': 0x41, 'params_num': 3, 'fmt':'<HbIII'}, 
            'gradient': {'id': 0x42, 'params_num': 20, 'fmt':'<HbI'}, # this one is modified later
            'cylon': {'id': 0x43, 'params_num': 0, 'fmt': '<Hb'}, 
            'rainbow': {'id': 0x44, 'params_num': 0, 'fmt':'<Hb'}, 
            'stroboscope': {'id': 0x45, 'params_num': 0, 'fmt': '<Hb'}, 
            'confetti': {'id': 0x46, 'params_num': 0, 'fmt': '<Hb'}, 
            'sinelon': {'id': 0x47, 'params_num': 0, 'fmt': '<Hb'}, 
            'bpm': {'id': 0x48, 'params_num': 0, 'fmt': '<Hb'}, 
            'juggle': {'id': 0x49, 'params_num': 0, 'fmt': '<Hb'}, 
            'fadeinout': {'id': 0x4A, 'params_num': 0, 'fmt': '<HIb'}, 
            'twinkle': {'id': 0x4B, 'params_num': 0, 'fmt': '<Hb'}, 
            'snowsparkle': {'id': 0x4C, 'params_num': 2, 'fmt': '<HbII'}, 
            'train': {'id': 0x4D, 'params_num': 1, 'fmt': '<HbI'}, 
            'wipe': {'id': 0x4E, 'params_num': 1, 'fmt': '<HbI'}, 
            'rainbow_classic': {'id': 0x4F, 'params_num': 0, 'fmt': '<Hb'}, 
            'theater_chase': {'id': 0x50, 'params_num': 3, 'fmt': '<HbIII'}, 
            'fire': {'id': 0x51, 'params_num': 0, 'fmt': '<Hb'}, 
            'segments': {'id': 0x52, 'params_num': 20, 'fmt':'<Hb'}, # this one is modified later
    }

    def __init__(self, port):
        try:
            self.serial = SerialTransport(port)
        except serial.SerialException:
            print(f'Could not open the {port}')
            return
        self.comm = Simpap(self.serial)
    
        self.receiver = threading.Thread(target=self.rxdaemon, args=(self.comm,))
        self.receiver.setDaemon(True)
        self.receiver.start()

        atexit.register(self.stop)

    def send(self, message):
        try:
            self.comm.send(message)
        except serial.SerialException:
            print(f'Could not send command "{cmd}"')
            self.stop()

    def rxdaemon(self, comm):
        t = threading.currentThread()
        while getattr(t, "running", True):
            try:
                if not comm.busy:
                    msg = comm.receive()
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

    def set_leds(self, num_leds):
        metadata = self.metadata['set_leds']
        message = self.comm.compose(metadata['fmt'], 
                [metadata['id'], metadata['params_num'], num_leds])
        self.send(message)

    def set_brightness(self, brightness):
        metadata = self.metadata['set_brightness']
        message = self.comm.compose(metadata['fmt'], 
                [metadata['id'], metadata['params_num'], brightness])
        self.send(message)

    def solid(self, color, offset=0, size=0):
        metadata = self.metadata['solid']
        message = self.comm.compose(metadata['fmt'], 
                [metadata['id'], metadata['params_num'], color, offset, size])
        self.send(message)

    def gradient(self, *argv):
        color_num = len(argv)
        metadata = self.metadata['gradient']
        fmt = metadata['fmt'] + 'i'*color_num
        message = self.comm.compose(fmt, 
                [metadata['id'], metadata['params_num'], color_num, *argv])
        self.send(message)

    def rainbow(self):
        metadata = self.metadata['rainbow']
        message = self.comm.compose(metadata['fmt'], 
                [metadata['id'], metadata['params_num']])
        self.send(message)

    def cylon(self):
        metadata = self.metadata['cylon']
        message = self.comm.compose(metadata['fmt'], 
                [metadata['id'], metadata['params_num']])
        self.send(message)

    def stroboscope(self):
        metadata = self.metadata['stroboscope']
        message = self.comm.compose(metadata['fmt'], 
                [metadata['id'], metadata['params_num']])
        self.send(message)

    def confetti(self):
        metadata = self.metadata['confetti']
        message = self.comm.compose(metadata['fmt'], 
                [metadata['id'], metadata['params_num']])
        self.send(message)

    def sinelon(self):
        metadata = self.metadata['sinelon']
        message = self.comm.compose(metadata['fmt'], 
                [metadata['id'], metadata['params_num']])
        self.send(message)

    def bpm(self):
        metadata = self.metadata['bpm']
        message = self.comm.compose(metadata['fmt'], 
                [metadata['id'], metadata['params_num']])
        self.send(message)

    def juggle(self):
        metadata = self.metadata['juggle']
        message = self.comm.compose(metadata['fmt'], 
                [metadata['id'], metadata['params_num']])
        self.send(message)

    def fadeinout(self):
        metadata = self.metadata['fadeinout']
        message = self.comm.compose(metadata['fmt'], 
                [metadata['id'], metadata['params_num']])
        self.send(message)

    def twinkle(self):
        metadata = self.metadata['twinkle']
        message = self.comm.compose(metadata['fmt'], 
                [metadata['id'], metadata['params_num']])
        self.send(message)

    def snowsparkle(self):
        metadata = self.metadata['snowsparkle']
        message = self.comm.compose(metadata['fmt'], 
                [metadata['id'], metadata['params_num']])
        self.send(message)

    def train(self):
        metadata = self.metadata['train']
        message = self.comm.compose(metadata['fmt'], 
                [metadata['id'], metadata['params_num']])
        self.send(message)

    def wipe(self):
        metadata = self.metadata['wipe']
        message = self.comm.compose(metadata['fmt'], 
                [metadata['id'], metadata['params_num']])
        self.send(message)

    def rainbow_classic(self):
        metadata = self.metadata['rainbow_classic']
        message = self.comm.compose(metadata['fmt'], 
                [metadata['id'], metadata['params_num']])
        self.send(message)

    def theater_chase(self):
        metadata = self.metadata['theater_chase']
        message = self.comm.compose(metadata['fmt'], 
                [metadata['id'], metadata['params_num']])
        self.send(message)

    def fire(self):
        metadata = self.metadata['fire']
        message = self.comm.compose(metadata['fmt'], 
                [metadata['id'], metadata['params_num']])
        self.send(message)

    def segments(self, *argv):
        color_num = len(argv)
        if color_num > 19:
            return
        metadata = self.metadata['segments']
        fmt = metadata['fmt'] + 'I'*color_num
        message = self.comm.compose(fmt, 
                [metadata['id'], color_num, *argv])
        self.send(message)
