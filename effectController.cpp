#include <cassert>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>

#include <wiringPi.h>

#include "effectController.h"

#include "lightsUtil.h"
#include "effect.h"
#include "mood.h"
#include "sorter.h"
#include "tracer.h"
#include "twinkle.h"
#include "rotate.h"

using namespace std;

#define SHOW_TIME_S 60 // Length of show in seconds


// Helper for looking at the "socket" file.
bool wasFileModifiedRecent(string path, time_t *last) {
  struct stat attr;
  stat(path.c_str(), &attr);

  double age = difftime(attr.st_mtime, *last);
  if (age > 1.0) {
    cout << "\t (age: " << age  << "): mtime: " << ctime(&attr.st_mtime);
    return true;
  }

  return false;
}

void EffectController::setupEffectController(
    int numLights, int updatesPerSecond, int latchTimeUS) {

  showTime_ = SHOW_TIME_S;
  numLights_ = numLights;
  updatesPerSecond_ = updatesPerSecond;
  latchTimeUS_ = latchTimeUS;
  
  USPerIter_ = 1000000 / updatesPerSecond;

  // Init to NOW.
  last_file_update_ = time(NULL);
}


bool EffectController::hasNewEffect() {
  if (effect_ == nullptr) {
    return true; // we haven't started yet!
  }

  //if (rand() % 10000 == 0) {
  //  return true; // Random effect change every x time;
  //}

  if (wasFileModifiedRecent("/tmp/light_show", &last_file_update_)) {
    return true;
  }

  return false;
}

bool EffectController::loadEffect() {
  cout << "\tloading new effect!" << endl;

  string show_name;

  if (wasFileModifiedRecent("/tmp/light_show", &last_file_update_)) {
    last_file_update_ = attr.st_mtime;
  }
  
  // Because this was easier!
  int rand_index = rand() % 4; // 0 to 6
  switch (rand_index) {
    case 0: 
      effect_.reset(new Mood()); break;
    case 1:
      effect_.reset(new Rotate()); break;
    case 2:
      effect_.reset(new Tracer()); break;
    case 3:
      effect_.reset(new Twinkle()); break;
    default:
      cout << "BAD rand_index" << endl;
      assert(false);
  }  

  // TODO looking in file location for recent update.

  //effect_.reset(new Twinkle());
  //effect_.reset(new Mood());
  //effect_.reset(new Tracer());
  //effect_.reset(new Sorter());
  //effect_.reset(new Rotate());
}

void EffectController::run() {
  round_ = 0;

  while (hasNewEffect()) {
    loadEffect();
    runEffect();
  }

  cout << "EffectController: No new effect; ending (rounds: " << round_ << ")" << endl;

  // BLANK LIGHTS AT END.
  int off[3] = {};
  for (int ci = 0; ci < numLights_; ci++) {
    writeColor(off);
  }
}

void EffectController::runEffect() {
  assert(numLights_ < 100);
  int colors[100][3] = {};
  effect_->setLights(numLights_, &colors);

  effect_->setupEffect();

  for (; round_ < updatesPerSecond_ * showTime_; round_++) {

    auto T0 = chrono::steady_clock::now();

    effect_->iterate();

    for (int ci = 0; ci < numLights_; ci++) {
      writeColor(colors[ci]);
    }

    auto T1 = chrono::steady_clock::now();
    auto duration = (chrono::duration_cast<chrono::microseconds> (T1 - T0)).count();
    int pauseUS = max((long long) latchTimeUS_, USPerIter_ - duration);

    if (round_ % 100 == 0) {
      cout << "round: " << round_ << " (" << duration << " us, pausing " << pauseUS << ")" << endl;
    }

    if (round_ % 100 == 50) {
      if (hasNewEffect()) {
        // Prempted
        return; 
      }
    }

    delayMicroseconds(pauseUS);
  }

  // Successfully finished effect (showTime expired!)
  return;
}
