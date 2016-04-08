#include <cassert>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>

#include <wiringPi.h>

#include "lightsUtil.h"


using namespace std;


#define NUM_LIGHTS 47
#define UPDATES_PER_SECOND 50
#define CYCLE_DELAY_US (1000000 / UPDATES_PER_SECOND)
#define APPROX_WRITE_DELAY_US (NUM_LIGHTS * 24 * WRITE_DELAY_US * 3)
#define LATCH_TIME_US 800 // ~>280us works but safety margin is good


int main(void) {
  assert(CYCLE_DELAY_US - APPROX_WRITE_DELAY_US > LATCH_TIME_US);

  setupLights();

  // Give program higher priority to affect more real timeness.
  piHiPri(20);

  // Init random.
  srand(time(0));

  cout << "Hello to Lights Master!" << endl;

  int colors[NUM_LIGHTS][3] = {};
  for (int ci = 0; ci < NUM_LIGHTS; ci++) {
      colors[ci][0] = 128;
      colors[ci][1] = 128;
      colors[ci][2] = 128;
  }

  for (int round = 0; round < 1000; round++) {
    if (round % 100 == 0) {
      cout << "round: " << round << endl;
    }

    for (int ci = 0; ci < NUM_LIGHTS; ci++) {
      colors[ci][0] = max(0, colors[ci][0] - 1);
      colors[ci][1] = max(0, colors[ci][1] - 1);
      colors[ci][2] = max(0, colors[ci][2] - 1);

      writeColor(colors[ci]);
    }

    delayMicroseconds(CYCLE_DELAY_US - APPROX_WRITE_DELAY_US);
  }

  return 0;
}
