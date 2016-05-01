#include <cassert>
#include <cmath>
#include <iostream>

#include "mood.h"

using namespace std;

void Mood::setupEffect() {
  /////////// CONFIG STARTS HERE ///////////

  cyclesPerColor = 150;

  // These defines how wide an area a new color will effect.
  oddScaler = 2.0;
  spread = 2.5;
  movePercent = 0.01;

  decayRate = 15;

  //////////// CONFIG ENDS HERE ////////////

  goalIndex = (goalIndex + randomInt(n / 4, n / 2)) % n;

  // two Colors can be high (> 100)
  // one Color must be low
  int lowIndex = randomInt(0, 2);

  for (int part = 0; part < 3; part++) {
    // Only one color is allowed to cross boundaries
    int newC = randomInt(155, 255);
    if (part == lowIndex) {
      newC = randomInt(0, 20);
    }
    goalColor[part] = newC;
  }

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
    float odds = spread * exp((deltaPos * deltaPos) / (2.0 * spread * spread));

    if (oneInX(odds / oddScaler)) {
      for (int part = 0; part < 3; part++) {
        int c = (*colors)[ci][part];
        int goal = goalColor[part] * (1.0 - deltaPos / 10);
        int delta = goal - c;
        int deltaDir = clamp(delta, -1, 1);

        // move slightly towards color;
        float amount = delta * movePercent;
//        cout << ci << " " << amount << endl;
        
        int intPart = trunc(amount);
        int remainder = abs(amount - intPart);

        (*colors)[ci][part] += intPart;
        if (oneInX(remainder)) {
          (*colors)[ci][part] += deltaDir;
        }         
      }
    }

    // Always be slightly fading towards black
    if (oneInX(decayRate)) {
      for (int part = 0; part < 3; part++) {
        int c = (*colors)[ci][part];

        int newC = c * (1 - movePercent);
        if (c < 2) {
           newC = 0;
        }
        (*colors)[ci][part] = newC;
      }
    }
  }
}
