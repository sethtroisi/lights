#include <cassert>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <fstream>
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

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>

using namespace std;

#define SHOW_TIME_S 60 // Length of show in seconds

#define LIGHT_FILE "/tmp/light_show"


// Helper for looking at the "socket" file.
bool wasFileModifiedRecent(string path, time_t *last, time_t *file_mtime) {
  struct stat attr;
  stat(path.c_str(), &attr);

  double age = difftime(attr.st_mtime, *last);

  if (file_mtime != nullptr) {
    *file_mtime = attr.st_mtime;
  }

  if (age > 1.0) {
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

  if (wasFileModifiedRecent(LIGHT_FILE, &last_file_update_, nullptr)) {
    return true;
  }

  return false;
}

bool EffectController::loadEffect() {
  string effect_name;

  if (wasFileModifiedRecent(LIGHT_FILE, &last_file_update_, &last_file_update_)) {
    try
    {
      using boost::property_tree::ptree;
      using boost::property_tree::read_json;

      ifstream ifs(LIGHT_FILE);
      ptree pt;
      read_json(ifs, pt);

      ptree::const_iterator end = pt.end();
      for (ptree::const_iterator it = pt.begin(); it != end; ++it) {
        string key = it->first;
        string value = it->second.get_value<string>();

        if (key == "show") {
          effect_name = value;
          cout << "\tLIGHT_FILE asked for " << value << endl;
        }

        if (key != "show" && key != "duration" && key != "parameter") {
          cout << "\tBAD KEY in LIGHT_FILE key: " << key << " : " << value << endl;
        }
      }
    }
    catch (std::exception const& e)
    {
      cerr << "Error reading light_file (" << LIGHT_FILE << "):";
      cerr << e.what() << endl;
    }
  }
 
  if (effect_name.empty()) {
    cout << "\tLoading random effect" << endl;

    // Twinkle is best effect so add it twice.
    vector<string> fun_effects = {"mood", "rotate", "tracer", "twinkle", "twinkle"};
 
    effect_name = fun_effects[rand() % fun_effects.size()];
    
    // Force a particuraly effect.
    //effect_name = "twinkle";
  }

  cout << "Loading Effect: " << effect_name << endl;
  if (effect_name == "mood") {
    effect_.reset(new Mood());
  } else if (effect_name == "rotate") {
    effect_.reset(new Rotate());
  } else if (effect_name == "tracer") {
    effect_.reset(new Tracer());
  } else if (effect_name == "twinkle") {
    effect_.reset(new Twinkle());
  } else {
    cout << "BAD effect_name: " << effect_name << endl;;
  }  
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

    if (round_ % 1000 == 0) {
      cout << "round: " << round_ << " (" << duration << " us, pausing " << pauseUS << ")" << endl;
    }

    if (round_ % updatesPerSecond_ == 1) {
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
