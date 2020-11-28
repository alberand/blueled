#!/bin/python

import numpy as np
import skimage.io
import skimage.filters
import skimage.transform
from mss.linux import MSS as mss
import time
import os, sys, inspect

# Add 'simpap' to the import path
currentdir = os.path.dirname(os.path.abspath(inspect.getfile(inspect.currentframe())))
parentdir = os.path.dirname(currentdir)
sys.path.insert(0, parentdir) 

import simpap

c = simpap.Blueled('/dev/ttyUSB0')
num_leds = 120
c.set_leds(num_leds)

def get_borders(img, size, num_segments=5):
	bw = 5
	mask = np.zeros(img.shape[0:2], dtype=bool)
	mask[mask.ndim * (slice(bw, -bw),)] = True 

	top = img[0:bw, 0:img.shape[1]]
	right = np.transpose(img[bw:(img.shape[0] - bw), (img.shape[1] - bw):img.shape[1]], (1, 0, 2))
	bottom = np.flip(img[img.shape[0] - bw:img.shape[0], 0:img.shape[1]], 1)
	left = np.flip(np.transpose(img[bw:(img.shape[0] - bw), 0:bw], (1, 0, 2)), 1)
	final = np.hstack([top, right, bottom, left])
	
	gradient = skimage.transform.resize(final, (1, int(size/num_segments)), anti_aliasing=False, order=3)
	
	return gradient

def rgb2int(rgb):
	return (int(rgb[0]*255) << 16) + (int(rgb[1]*255) << 8) + (int(rgb[2]*255) << 0)

def int2rgb(num):
	return (((num >> 16) & 0xFF)/255, ((num >> 8) & 0xFF)/255, ((num >> 0) & 0xFF)/255)

def loop():
	with mss() as sct:
		for _ in range(10):
			f = sct.shot()

			# Read create screenshot
			img = skimage.io.imread(f)
			small = skimage.transform.resize(img, (108, 192), anti_aliasing=True)

			# Blur
			sigma = 3
			blurred = skimage.filters.gaussian(small, sigma=sigma, truncate=3.5, multichannel=True)

			segments = get_borders(small, num_leds, 20)

			colors = [rgb2int(c) for c in segments[0]]
			c.segments(*colors)
			# c.solid(colors[0])

			time.sleep(0.5)

if __name__ == '__main__':
	print('Extend screen with LEDs')

	try:
		loop()
	except KeyboardInterrupt as e:
		print('Exiting')
		print(e)
		c.stop()
