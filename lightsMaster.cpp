#include <cassert>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>

#include <wiringPi.h>

#include "effectController.h"
#include "lightsUtil.h"

using namespace std;

#define NUM_LIGHTS 27
#define UPDATES_PER_SECOND 50
#define LATCH_TIME_US 550 // ~300us works but safety margin is good

int main(void) {

  // Give program higher priority to affect more real timeness.
  piHiPri(40);

  // Init random.
  srand(time(0));

  // setup lights (GPIO, ...)
  setupLights();

  cout << "Hello to Lights Master!" << endl;

  // Set up EffectController to deal with everything.
  EffectController controller;
  controller.setupEffectController(
      NUM_LIGHTS,
      UPDATES_PER_SECOND,
      LATCH_TIME_US);

  controller.run();

  // BLANK LIGHTS AT END.
  int off[3] = {};
  for (int ci = 0; ci < NUM_LIGHTS; ci++) {
    writeColor(off);
  }

  return 0;
}
