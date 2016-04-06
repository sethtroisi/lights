import RPi.GPIO as GPIO
import math
import random
import time

print "Hello World"

GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)

dataChannel = 3
clockChannel = 2

channels = [dataChannel, clockChannel]

GPIO.setup(channels, GPIO.OUT)


def randomColor(bitsPerColor = 8):
	maxColor = (1 << bitsPerColor) - 1
	midColor = maxColor / 2

	def weirdRandom():
		# inverseTriangle
		direction = 2 * random.randint(0, 1) - 1
		
		range = int(random.triangular(0, midColor, midColor))
		return midColor + direction * range

	# prefer colors closer to 0 or max (avoid middle)
	return tuple(weirdRandom() for i in range(3))


def sendBit(bit):
	assert bit in (True, False, 0, 1)
	GPIO.output(dataChannel, bit)
	GPIO.output(clockChannel, GPIO.HIGH)
	GPIO.output(clockChannel, GPIO.LOW)

def sendNumberAsBits(number):
	assert 0 <= number <= 255
	for bit in range(8):
		data = (number & (1 << bit)) > 0
		sendBit(data)

def sendColor(rgb):
	for component in rgb:
		sendNumberAsBits(component)


def colorSequence():
	#sendBits([0,1,0,0])

	colorDelay = 2

	colors = [(255,255,255), (255,0,0), (0,255,0), (0,0,255)]
	for i in range(1000):
		colors.append(colors[random.randint(0,4)])

#	for i in range(1000):	
#		colors.append(randomColor())

	major = random.randint(0,2)
	for i in range(1, 20):
		for lightNum in range(i+1):
			color = [0, 0, 0]
			color[major] = 255 - 20 * lightNum

			print "Setting light {} to {}".format(lightNum, color)
			sendColor(color)

		print 
		# Data is latched by holding clock pin low for > 1 milli
		time.sleep(colorDelay)

	'''
	lightsAtATime = 8

	chucks = [colors[x:x+lightsAtATime]
		for x in range(0, len(colors), lightsAtATime)]

	for colorBlock in chucks:
		for lightNum, color in enumerate(colorBlock):
			print "Setting light {} to {}".format(lightNum, color)
			sendColor(color)

		print 
		# Data is latched by holding clock pin low for > 1 milli
		time.sleep(colorDelay)
	'''

colorSequence()
