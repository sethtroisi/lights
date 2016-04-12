#include <cassert>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>

#include <wiringPi.h>

#include "lightsUtil.h"
#include "effect.h"
#include "tracer.h"

using namespace std;

#define SHOW_TIME_S 1000 // Length of show in seconds

#define NUM_LIGHTS 48
#define UPDATES_PER_SECOND 50
#define CYCLE_DELAY_US (1000000 / UPDATES_PER_SECOND)
#define APPROX_WRITE_DELAY_US (NUM_LIGHTS * 24 * WRITE_DELAY_US * 3)
#define LATCH_TIME_US 800 // ~>280us works but safety margin is good

int main(void) {
  assert(CYCLE_DELAY_US - APPROX_WRITE_DELAY_US > LATCH_TIME_US);

  // Give program higher priority to affect more real timeness.
  piHiPri(20);

  // Init random.
  srand(time(0));

  // setup lights (GPIO, ...)
  setupLights();

  cout << "Hello to Lights Master!" << endl;

  int colors[NUM_LIGHTS][3] = {};
  for (int ci = 0; ci < NUM_LIGHTS; ci++) {
      colors[ci][0] = 128;
      colors[ci][1] = 128;
      colors[ci][2] = 128;
  }

  Tracer tracer;
  tracer.setNumLights(NUM_LIGHTS);
  tracer.setupEffect(colors);


  for (int round = 0; round < UPDATES_PER_SECOND * SHOW_TIME_S; round++) {
    if (round % 100 == 0) {
      cout << "round: " << round << endl;
    }

    // TODO WRITE LED SORTER (by value from random init)
    tracer.iterate(colors);

    for (int ci = 0; ci < NUM_LIGHTS; ci++) {
      writeColor(colors[ci]);
    }

    delayMicroseconds(CYCLE_DELAY_US - APPROX_WRITE_DELAY_US);
  }

  // BLANK LIGHTS AT END.
  int off[3] = {};
  for (int ci = 0; ci < NUM_LIGHTS; ci++) {
    writeColor(off);
  }

  return 0;
}
