#include <cassert>
#include <cmath>
#include <iostream>

#include "rotate.h"

using namespace std;

void Rotate::setupEffect() {
  /////////// CONFIG STARTS HERE ///////////

  cyclesPerPos = 3;
  wheelPosPerIndex = 2;

  wheelPos =  200;
  //////////// CONFIG ENDS HERE ////////////
};  

void Rotate::iterate() {
  iter++;
  wheelPos = (wheelPos + (iter % cyclesPerPos == 0)) % 255;

  for (int i = 0; i < n; i++) {
    setWheelColor(i, (wheelPos + wheelPosPerIndex * i) % 255);
  }
}

void Rotate::setWheelColor(int i, int wp) {
  if(wp < 85) {
   setColor(i, 255 - 3 * wp, 0, 3 * wp, *colors);
  } else if(wp < 170) {
    wp -= 85;
    setColor(i, 0, 3 * wp, 255 - 3 * wp, *colors);
  } else {
    wp -= 170;
    setColor(i, 3 * wp, 255 - 3 * wp, 0, *colors);
  }
}
