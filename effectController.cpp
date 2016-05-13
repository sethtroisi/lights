#include <cassert>
#include <chrono>
#include <iostream>

#include <wiringPi.h>

#include "effectController.h"

#include "lightsUtil.h"
#include "effect.h"
#include "mood.h"
#include "sorter.h"
#include "tracer.h"
#include "twinkle.h"

using namespace std;


void EffectController::setupEffectController(
    int showTime, int numLights, int updatesPerSecond, int latchTimeUS) {

  showTime_ = showTime;
  numLights_ = numLights;
  updatesPerSecond_ = updatesPerSecond;
  latchTimeUS_ = latchTimeUS;
  
  USPerIter_ = 1000000 / updatesPerSecond;
}


void EffectController::run() {
  assert(numLights_ < 100);
  int colors[100][3] = {};

  Effect* effect = new Mood();
  //Effect* effect = new Sorter();
  //Effect* effect = new Tracer();
  //Effect* effect = new Twinkle();

  effect->setLights(numLights_, &colors);
  effect->setupEffect();


  for (int round = 0; round < updatesPerSecond_ * showTime_; round++) {
    auto T0 = chrono::steady_clock::now();

    effect->iterate();

    for (int ci = 0; ci < numLights_; ci++) {
      writeColor(colors[ci]);
    }

    auto T1 = chrono::steady_clock::now();
    auto duration = (chrono::duration_cast<chrono::microseconds> (T1 - T0)).count();
    int pauseUS = max((long long) latchTimeUS_, USPerIter_ - duration);

    if (round % 100 == 0) {
      cout << "round: " << round << " (" << duration << " us, pausing " << pauseUS << ")" << endl;
    }

    delayMicroseconds(pauseUS);
  }

  // BLANK LIGHTS AT END.
  int off[3] = {};
  for (int ci = 0; ci < numLights_; ci++) {
    writeColor(off);
  }
}
