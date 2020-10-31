import time
import atexit

import os, sys, inspect
currentdir = os.path.dirname(os.path.abspath(inspect.getfile(inspect.currentframe())))
parentdir = os.path.dirname(currentdir)
sys.path.insert(0, parentdir) 

import simpap

c = simpap.Blueled('/dev/ttyUSB0')
atexit.register(c.stop)

pause = 0.05
time.sleep(1)

for i in range(400):
    c.solid(0xFF0000)
    time.sleep(pause)
    c.solid(0x00FF00)
    time.sleep(pause)
