#include <cassert>
#include <cmath>
#include <iostream>

#include "bubble.h"

using namespace std;

void Bubble::setupEffect() {
  /////////// CONFIG STARTS HERE ///////////

  cyclesPerColor = 8 * 50;

  // These defines how wide an area a new color will effect.
  spread = 4;

  effectRate = 0.005;
  decayRate  = 0.0001;

  //////////// CONFIG ENDS HERE ////////////

  for (int b = 0; b < bubble_count; b++) {
    int goalColor[3];
    goalColor[0] = randomInt(140,255);
    goalColor[1] = randomInt(10,40);
    goalColor[2] = randomInt(0,20);

    // shuffle
    swap(goalColor[2], goalColor[randomInt(0,2)]);
    swap(goalColor[1], goalColor[randomInt(0,1)]);

    bubble_color[b][0] = goalColor[0];
    bubble_color[b][0] = goalColor[0];
    bubble_color[b][0] = goalColor[0];

    bubble_index[b] = randomInt(0, n);
    bubble_veloc[b] = 3 * randomFloat() - 1.5;
  }
};  

void Bubble::iterate() {
  iter++;

//  if (oneInX(cyclesPerColor)) {
//    setupEffect();
//  }


  for (int ci = 0; ci < n; ci++) {
    for (int b = 0; b < bubble_count; b++) {
      int goalIndex = bubble_index[b];
      int *goalColor = bubble_color[b];

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
  }

  setColorsFromFloat(10);
}
