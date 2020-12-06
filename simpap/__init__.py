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
    header = '<Hb'

    metadata = {
            'set_leds': {'id': 0x20, 'fmt':'I'}, 
            'set_brightness': {'id': 0x21, 'fmt':'I'}, 
            'solid': {'id': 0x41, 'fmt':'III'}, 
            'gradient': {'id': 0x42, 'fmt': ''}, # this one is modified later
            'cylon': {'id': 0x43, 'fmt': ''}, 
            'rainbow': {'id': 0x44, 'fmt':''}, 
            'stroboscope': {'id': 0x45, 'fmt': ''}, 
            'confetti': {'id': 0x46, 'fmt': ''}, 
            'sinelon': {'id': 0x47, 'fmt': ''}, 
            'bpm': {'id': 0x48, 'fmt': ''}, 
            'juggle': {'id': 0x49, 'fmt': ''}, 
            'fadeinout': {'id': 0x4A, 'fmt': 'I'}, 
            'twinkle': {'id': 0x4B, 'fmt': ''}, 
            'snowsparkle': {'id': 0x4C, 'fmt': ''}, 
            'train': {'id': 0x4D, 'fmt': 'I'}, 
            'wipe': {'id': 0x4E, 'fmt': 'I'}, 
            'rainbow_classic': {'id': 0x4F, 'fmt': ''}, 
            'theater_chase': {'id': 0x50, 'fmt': 'III'}, 
            'fire': {'id': 0x51, 'fmt': ''}, 
            'segments': {'id': 0x52, 'fmt': ''}, # this one is modified later
            'gradient_pos': {'id': 0x53, 'fmt': 'IIII'},
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

    def command(self, metadata, msg_fmt, msg_data):
        fmt = self.header + msg_fmt
        data = [metadata['id'], len(msg_data), *msg_data]

        message = self.comm.compose(fmt, data)
        self.send(message)

    def set_leds(self, num_leds):
        metadata = self.metadata['set_leds']
        self.command(metadata, metadata['fmt'], [num_leds])

    def set_brightness(self, brightness):
        metadata = self.metadata['set_brightness']
        self.command(metadata, metadata['fmt'], [brightness])

    def solid(self, color, offset=0, size=0):
        metadata = self.metadata['solid']
        self.command(metadata, metadata['fmt'], [color, offset, size])

    def clear(self):
        metadata = self.metadata['solid']
        self.command(metadata, metadata['fmt'], [0, 0, 0])

    def gradient(self, *argv):
        if len(argv) > 19:
            return
        metadata = self.metadata['gradient']
        fmt = metadata['fmt'] + 'i'*len(argv)
        self.command(metadata, fmt, argv)

    def rainbow(self):
        metadata = self.metadata['rainbow']
        self.command(metadata, metadata['fmt'], [])

    def cylon(self):
        metadata = self.metadata['cylon']
        self.command(metadata, metadata['fmt'], [])

    def stroboscope(self):
        metadata = self.metadata['stroboscope']
        self.command(metadata, metadata['fmt'], [])

    def confetti(self):
        metadata = self.metadata['confetti']
        self.command(metadata, metadata['fmt'], [])

    def sinelon(self):
        metadata = self.metadata['sinelon']
        self.command(metadata, metadata['fmt'], [])

    def bpm(self):
        metadata = self.metadata['bpm']
        self.command(metadata, metadata['fmt'], [])

    def juggle(self):
        metadata = self.metadata['juggle']
        self.command(metadata, metadata['fmt'], [])

    def fadeinout(self, color):
        metadata = self.metadata['fadeinout']
        self.command(metadata, metadata['fmt'], [color])

    def twinkle(self):
        metadata = self.metadata['twinkle']
        self.command(metadata, metadata['fmt'], [])

    def snowsparkle(self):
        metadata = self.metadata['snowsparkle']
        self.command(metadata, metadata['fmt'], [])

    def train(self):
        metadata = self.metadata['train']
        self.command(metadata, metadata['fmt'], [])

    def wipe(self):
        metadata = self.metadata['wipe']
        self.command(metadata, metadata['fmt'], [])

    def rainbow_classic(self):
        metadata = self.metadata['rainbow_classic']
        self.command(metadata, metadata['fmt'], [])

    def theater_chase(self):
        metadata = self.metadata['theater_chase']
        self.command(metadata, metadata['fmt'], [])

    def fire(self):
        metadata = self.metadata['fire']
        self.command(metadata, metadata['fmt'], [])

    def segments(self, *argv):
        if len(argv) > 19:
            return
        metadata = self.metadata['segments']
        fmt = metadata['fmt'] + 'I'*len(argv)
        self.command(metadata, fmt, argv)

    def gradient_pos(self, offset, length, c1, c2):
        metadata = self.metadata['gradient_pos']
        self.command(metadata, metadata['fmt'], [offset, length, c1, c2])
