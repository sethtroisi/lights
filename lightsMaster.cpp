#include <cassert>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>

#include <wiringPi.h>

#include "lightsUtil.h"
#include "effect.h"
#include "mood.h"
#include "sorter.h"
#include "tracer.h"
#include "twinkle.h"

using namespace std;

#define SHOW_TIME_S 2 * 3600 // Length of show in seconds

#define NUM_LIGHTS 42
#define UPDATES_PER_SECOND 50
#define CYCLE_DELAY_US (1000000 / UPDATES_PER_SECOND)
#define APPROX_WRITE_DELAY_US (NUM_LIGHTS * 24 * WRITE_DELAY_US * 2)
#define LATCH_TIME_US 550 // ~300us works but safety margin is good

int main(void) {
  assert(CYCLE_DELAY_US - APPROX_WRITE_DELAY_US > LATCH_TIME_US);

  // Give program higher priority to affect more real timeness.
  piHiPri(40);

  // Init random.
  srand(time(0));

  // setup lights (GPIO, ...)
  setupLights();

  cout << "Hello to Lights Master!" << endl;

  assert(NUM_LIGHTS < 100);
  int colors[100][3] = {};

  //Effect* effect = new Mood();
  //Effect* effect = new Sorter();
  //Effect* effect = new Tracer();
  Effect* effect = new Twinkle();

  effect->setLights(NUM_LIGHTS, &colors);
  effect->setupEffect();


  for (int round = 0; round < UPDATES_PER_SECOND * SHOW_TIME_S; round++) {
    if (round % 100 == 0) {
      cout << "round: " << round << endl;
    }

    effect->iterate();

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
