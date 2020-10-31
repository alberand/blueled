import simpap
import time
import atexit

c = simpap.Communication('/dev/ttyUSB0')
atexit.register(c.stop)

pause = 0
time.sleep(1)

c.cmd('l1')
for i in range(4):
    c.cmd('s00FF0000')
    time.sleep(pause)
    c.cmd('s0000FF00')
    time.sleep(pause)

c.cmd('l5')
for i in range(4):
    c.cmd('s000000FF')
    time.sleep(pause)
    c.cmd('g')
    time.sleep(pause)

c.stop()
