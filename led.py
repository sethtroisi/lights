import RPi.GPIO as GPIO
import math
import time

print "Hello World"

GPIO.setmode(GPIO.BCM)


channel = 3

GPIO.setup(channel, GPIO.OUT)

freq = 10
interval = 1.0 / freq

onInterval = 3 * interval
offInterval = interval


for i in range(1, 1000):
	GPIO.output(channel, GPIO.HIGH)
	time.sleep(onInterval)
	GPIO.output(channel, GPIO.LOW)
	time.sleep(offInterval)

