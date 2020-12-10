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
        'thunderstorm with light rain': 0x0,
        'thunderstorm with rain': 0x0,
        'thunderstorm with heavy rain': 0x0,
        'light thunderstorm': 0x0,
        'thunderstorm': 0x0,
        'heavy thunderstorm': 0x0,
        'ragged thunderstorm': 0x0,
        'thunderstorm with light drizzle': 0x0,
        'thunderstorm with drizzle': 0x0,
        'thunderstorm with heavy drizzle': 0x0,
        'light intensity drizzle': 0x0,
        'drizzle': 0x0,
        'heavy intensity drizzle': 0x0,
        'light intensity drizzle rain': 0x0,
        'drizzle rain': 0x0,
        'heavy intensity drizzle rain': 0x0,
        'shower rain and drizzle': 0x0,
        'heavy shower rain and drizzle': 0x0,
        'shower drizzle': 0x0,
        'light rain': 0x0,
        'moderate rain': 0x0,
        'heavy intensity rain': 0x0,
        'very heavy rain': 0x0,
        'extreme rain': 0x0,
        'freezing rain': 0x0,
        'light intensity shower rain': 0x0,
        'shower rain': 0x0,
        'heavy intensity shower rain': 0x0,
        'ragged shower rain': 0x0,
        'light snow': 0x0,
        'Snow': 0x0,
        'Heavy snow': 0x0,
        'Sleet': 0x0,
        'Light shower sleet': 0x0,
        'Shower sleet': 0x0,
        'Light rain and snow': 0x0,
        'Rain and snow': 0x0,
        'Light shower snow': 0x0,
        'Shower snow': 0x0,
        'Heavy shower snow': 0x0,
        'mist': 0x0,
        'Smoke': 0x0,
        'Haze': 0x0,
        'sand/ dust whirls': 0x0,
        'fog': 0x0,
        'sand': 0x0,
        'dust': 0x0,
        'volcanic ash': 0x0,
        'squalls': 0x0,
        'tornado': 0x0,
        'clear sky': 0x0,
        'scattered clouds': 0x0,
        'broken clouds': 0x0,
        'overcast clouds': 0x03bafc,
}

def get_current_weather():
    # Search for current weather in London (Great Britain) and get details
    observation = mgr.weather_at_place('London,GB')
    w = observation.weather
    
    return w.detailed_status

def loop():
    while True:
        state = get_current_weather()
        print('Weather status {state}')
        c.solid(colorsmap[state])
        time.sleep(2)

if __name__ == '__main__':
    print('Extend screen with LEDs')

    try:
        loop()
    except KeyboardInterrupt as e:
        print('Exiting')
        print(e)
        c.stop()
