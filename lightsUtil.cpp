#include <cassert>
#include <iostream>

#include <wiringPi.h>

#include "lightsUtil.h"


using namespace std;

void writeBit(bool bit) {
    digitalWrite (DATA_PORT, bit);     // data
    delayMicroseconds(WRITE_DELAY_US);

    digitalWrite (CLOCK_PORT, 1);       // CLK up
    delayMicroseconds(WRITE_DELAY_US);

    digitalWrite (CLOCK_PORT, 0);       // CLK down
    delayMicroseconds(WRITE_DELAY_US);
}

void writeByte(int num) {
    assert (num >= 0);
    assert (num <= 255);

    for (int bit = 128; bit > 0; bit >>= 1) {
        writeBit((num & bit) > 0);
    }
}

void writeColor(int color[]) {
    writeByte(color[0]);
    writeByte(color[1]);
    writeByte(color[2]);
}

void setupLights(void) {
  if (wiringPiSetup () == -1) {
    cout << "wiringPiSetup failed" << endl;
    exit;
  }

  pinMode (CLOCK_PORT, OUTPUT);
  pinMode (DATA_PORT, OUTPUT);

}

// DELAY LATCH ~280us = .28ms
