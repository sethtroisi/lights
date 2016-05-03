#include <cassert>
#include <cmath>
#include <iostream>

#include "mood.h"

using namespace std;

void Mood::setupEffect() {
  /////////// CONFIG STARTS HERE ///////////

  cyclesPerColor = 8 * 50;

  // These defines how wide an area a new color will effect.
  spread = 4;

  effectRate = 0.005;
  decayRate  = 0.0001;

  //////////// CONFIG ENDS HERE ////////////

  goalIndex = randomInt(0, n-1);

  goalColor[0] = randomInt(140,255);
  goalColor[1] = randomInt(10,40);
  goalColor[2] = randomInt(0,20);

  // shuffle
  swap(goalColor[2], goalColor[randomInt(0,2)]);
  swap(goalColor[1], goalColor[randomInt(0,1)]);

  cout << "\theading towards ";
  cout << goalColor[0] << ", " << goalColor[1] << ", " << goalColor[2] << " @ " << goalIndex << endl;
};  

void Mood::iterate() {
  iter++;

  if (oneInX(cyclesPerColor)) {
    setupEffect();
  }

  for (int ci = 0; ci < n; ci++) {
    // chance of update.
    int deltaPos = min(abs(ci - goalIndex), abs(ci - n - goalIndex));
    float positionRate = 1.0/spread * exp(-(deltaPos * deltaPos) / (2.0 * spread * spread));

    for (int part = 0; part < 3; part++) {
      float c = floatColor[ci][part];
      int goal = goalColor[part];
      float delta = goal - c;

      // move slightly towards color;
      float amount = delta * positionRate * effectRate;

//      cout << ci << " " << positionRate << " | " << part << delta << " " << effectRate << endl;

      floatColor[ci][part] += amount;
    }

    // Always be slightly fading towards black
    for (int part = 0; part < 3; part++) {
      floatColor[ci][part] *= (1 - decayRate);

//      cout << ci << " " << part << " " << floatColor[ci][part] << endl;;
    }
  }

  setColorsFromFloat(10);
}
