#!/bin/python

import time
import os, sys, inspect

# Weather API
from pyowm import OWM
from pyowm.utils import config
from pyowm.utils import timestamps

# Add 'simpap' to the import path
currentdir = os.path.dirname(os.path.abspath(inspect.getfile(inspect.currentframe())))
parentdir = os.path.dirname(currentdir)
sys.path.insert(0, parentdir) 

import simpap

# Interface to LED strip
c = simpap.Blueled('/dev/ttyUSB0')
num_leds = 120
c.set_leds(num_leds)

# API
if 'OWM_API_KEY' not in os.environ:
	print('Environment variable "OWM_API_KEY" is not defined')
	sys.exit(1)

owm = OWM(os.environ['OWM_API_KEY'])
mgr = owm.weather_manager()

colorsmap = {
	'rain': 0x0000FF,
	'light rain': 0x000088,
	'sunny': 0xFF8400,
}

def get_current_weather():
	# Search for current weather in London (Great Britain) and get details
	observation = mgr.weather_at_place('London,GB')
	w = observation.weather
	
	print(w.detailed_status)
	print(w.wind())
	print(w.humidity)
	print(w.temperature('celsius'))
	print(w.rain)
	print(w.heat_index)
	print(w.clouds)

	return 'sunny'

def loop():
    while True:
        c.solid(colorsmap[get_current_weather()])
        time.sleep(2)

if __name__ == '__main__':
    print('Extend screen with LEDs')

    try:
        loop()
    except KeyboardInterrupt as e:
        print('Exiting')
        print(e)
        c.stop()
