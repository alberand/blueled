import os, sys, inspect
currentdir = os.path.dirname(os.path.abspath(inspect.getfile(inspect.currentframe())))
parentdir = os.path.dirname(currentdir)
sys.path.insert(0, parentdir) 

import time
import atexit
import colorsys

import simpap

def rainbow_color_stops(n=10, end=2/3):
        return [ [int(x*255.0) for x in colorsys.hls_to_rgb(end * i/(n-1), 0.5, 1)] 
                        for i in range(n) ]

def tuple_to_int(rgb):
    return (rgb[0] << 16) + (rgb[1] << 8) + rgb[2]


c = simpap.Blueled('/dev/ttyUSB0')
atexit.register(c.stop)

pause = 0.05
time.sleep(1)

# print(list(map(tuple_to_int, rainbow_color_stops())))
for i in list(map(tuple_to_int, rainbow_color_stops(200))):
    c.solid(i)
    time.sleep(pause)
