#!/usr/bin/env python3

import logging
import serial
import struct
import time
import random

LIGHTS = 15

MAGIC_HEADER = b'\x03\x05\x08\x0D'
LIGHT_NUM_HEADER = struct.pack('>I', 3 * LIGHTS)

def readAndSave():
  ser = serial.Serial('/dev/ttyACM0', 9600)

  raw_line = ser.readline().strip()
  print ("Raw: \"{}\"".format(raw_line))
  line = raw_line.decode('UTF-8').strip()
  print ("Recieved line: \"{}\"".format(line))
  if "StrandClient" not in line and "ACK" not in line:
    return

  iteration = 0

  test = time.time()
  while True:
    iteration += 1
    print (time.time() - test)
    test = time.time()

    #ser.write(MAGIC_HEADER)
    #ser.write(LIGHT_NUM_HEADER)
    for i in range(LIGHTS):
#      r = 5 * (i % 3)
#      g = 5 * (i % 5)
#      b = 5 * (i % 10)
      r = (iteration % 150) #+ random.randint(0,  50)
      g = 2 #random.randint(30, 50)
      b = 2 #random.randint(0,  20)

      color = struct.pack('BBB', r, g, b)
      assert len(color) == 3

      ser.write(color)

    time.sleep(1)

#    ser.flushInput()
    while True:
      line = ser.readline().decode('UTF-8').strip()
      print ("Debug line: \"{}\"".format(line))
      if "ACK" in line:
        break


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
    time.sleep(1)
