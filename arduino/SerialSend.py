#!/usr/bin/env python3

import logging
import serial
import time

LIGHTS = 10

MAGIC_HEADER = b'\x03\x05\x08\x0D'
LIGHT_NUM_HEADER = b'\x00\x00\x00' + chr(LIGHTS).encode('UTF-8')

def readAndSave():
  ser = serial.Serial('/dev/ttyACM0', 57600)

  line = ser.readline().decode('UTF-8').strip()
  print ("Recieved line: \"{}\"".format(line))
  if "StrandClient" not in line:
    return

  print ("Sending some fake data")

  ser.write(MAGIC_HEADER)
  ser.write(LIGHT_NUM_HEADER)
  for i in range(LIGHTS):
    r = 5 * (i % 3)
    g = 5 * (i % 5)
    b = 5 * (i % 10)

    color = (chr(r) + chr(g) + chr(b)).encode('UTF-8')
    ser.write(color)

  while True:
    line = ser.readline().decode('UTF-8').strip()

errorCount = 0
while errorCount < 10:
  try:
    readAndSave()
  except KeyboardInterrupt:
    logging.error('Caught KeyboardInterrupt, exitting')
    break
  except Exception as e:
    errorCount += 1
    logging.error("error {}: {}".format(errorCount, e))
    time.sleep(10)
