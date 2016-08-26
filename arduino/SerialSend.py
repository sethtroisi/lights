#!/usr/bin/env python3

import logging
import serial
import struct
import time
import random

LIGHTS = 45

MAGIC_HEADER = b'\x03\x05\x08\x0D'
LIGHT_NUM_HEADER = struct.pack('>I', 3 * LIGHTS)

def test():
  assert False, "Not tested or written yet"
  ser = serial.Serial('/dev/ttyUSB0', baudrate = 10000)

  print (ser.readline())
  ser.write("Hello")




def runIt():
  #ser = serial.Serial('/dev/ttyACM0', 9600)
  ser = serial.Serial('/dev/ttyUSB0', baudrate = 9600)

  #raw_line = ser.readline().strip()
  #print ("Raw: \"{}\"".format(raw_line))
  #line = raw_line.decode('UTF-8').strip()
  #print ("Recieved line: \"{}\"".format(line))
  #if "StrandClient" not in line and "ACK" not in line:
  #  return

  test = time.time()
  for iteration in range(25):
    for i in range(LIGHTS):
      ser.write(MAGIC_HEADER)
      ser.write(struct.pack('b', i))

      r = i
      g = 50 * (iteration % 4)
      b = 50 * (iteration % 2)

      color = struct.pack('BBB', r, g, b)
      assert len(color) == 3
      ser.write(color)

      if i % 4 == 0:
        ser.flush()
        # is time.sleep needed?
        time.sleep(0.00001)

    delta = time.time() - test
    print ("{:.5f} = {} baud".format(delta, LIGHTS * (len(MAGIC_HEADER) + 1 + 3) / delta))
    test = time.time()


runIt()

#errorCount = 0
#while errorCount < 10:
  #try:
  #  runIt()
  #except KeyboardInterrupt:
  #  logging.error('Caught KeyboardInterrupt, exitting')
  #  break
  #except Exception as e:
  #  errorCount += 1
  #  logging.error("error {}: {}".format(errorCount, e))
  #  time.sleep(1)
