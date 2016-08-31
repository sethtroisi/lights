#include <iostream>

#include "danger.h"

using namespace std;


void Danger::setupEffect() {

  /////////// CONFIG STARTS HERE ///////////

  numFlashes = 10;
  flashCycleDuration = 7; // Two Cycles on and off

  numTracers = 2; // Both back and forth
  tracerLength = 8;
  tracerCycleDuration = 1; // cycles per index

  for (int i = 0; i < n; i++) {
    setColor(i, 0 /* Red*/, 0 /* Green */, 0 /* Blue */, *colors);
  }

  //////////// CONFIG ENDS HERE ////////////

  showCycles = 2 * numFlashes * flashCycleDuration +
               2 * numTracers * tracerCycleDuration * n;
};  

void Danger::iterate() {
  if (iter == 0) {
      dangerColor[0] = 150;
      dangerColor[1] = randomInt(0, 10);
      dangerColor[2] = 0;
  }

  iter = (iter + 1) % showCycles;

  int flashCycles = 2 * numFlashes * flashCycleDuration;
  if (iter < flashCycles) {
    int state = iter % (2 * flashCycleDuration);

    int flashColor[3] = {0, 0, 0};
    if (state < flashCycleDuration) {
      // Set Lights on.
      flashColor[0] = dangerColor[0];
      flashColor[1] = dangerColor[1];
      flashColor[2] = dangerColor[2];
    }

    for (int i = 0; i < n; i++) {
      setColor(i, flashColor[0], flashColor[1], flashColor[2], *colors);
    }
  } else {
    int state = (iter - flashCycles) % (2 * tracerCycleDuration * n);
    bool movingRight = state < tracerCycleDuration * n;

    int index = state / tracerCycleDuration;
    if (index >= n) {
      index = (2 * n - 1) - index;
    }

    for (int i = 0; i < n; i++) {
      setColor(i, 0, 0, 0, *colors);
    }

    if (movingRight) {
      for (int i = max(0, index - tracerLength + 1); i <= index; i++) {
        setColor(i, dangerColor[0], dangerColor[1], dangerColor[2], *colors);
      }
    } else {
      for (int i = min(n - 1, index + tracerLength - 1); i >= index; i--) {
        setColor(i, dangerColor[0], dangerColor[1], dangerColor[2], *colors);
      }
    }
  }
}
