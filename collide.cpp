#include <iostream>

#include "collide.h"

using namespace std;


void Collide::setupEffect() {
  for (int i = 0; i < n; i++) {
    status[i] = 0;
    setColor(i, 0, 0, 0, localColor);
  }

  /////////// CONFIG STARTS HERE ///////////

  cyclesPerIndex = 5;
  decayPerCycle = 3;

  status[0] = cyclesPerIndex; // Start with an active "Trace"
  localColor[0][0] = 200;     // color to "trace" (RED)

  // Set background colors.
  //  Hint they all look ugly :(
  for (int i = 0; i < n; i++) {
    setColor(i, 0 /* Red*/, 1 /* Green */, 1 /* Blue */, saveColor);
  }

  //////////// CONFIG ENDS HERE ////////////
};  

void Collide::iterate() {
  if (oneInX(25 * cyclesPerIndex)) {

    status[0] = -cyclesPerIndex;
    status[n-1] = -cyclesPerIndex;

    int red = 84 * (rand() % 3);
    int green = 84 * (rand() % 3);
    int blue = 84 * (rand() % 3);

    setColor(0, red, green, blue, localColor);
    setColor(n - 1, red, green, blue, localColor);

    int red_afterglow = red >= green && red >= blue;
    int green_afterglow = green > red && green >= blue;
    int blue_afterglow = blue > red && blue > green;

    setColor(0, red_afterglow, green_afterglow, blue_afterglow, saveColor);
    setColor(n - 1, red_afterglow, green_afterglow, blue_afterglow, saveColor);
  }

  for (int ci = 0; ci < n; ci++) {
    int s = status[ci];
    if (s < 0) {
      status[ci] = -status[ci];
      continue;
    }

    if (s > 1) {
      status[ci] -= 1;
      continue;
    }

    for (int part = 0; part < 3; part++) {
      if (s == 1) {
        int c = localColor[ci][part];

        int next_ci;
        if (2 * ci > n) {
          next_ci = ci - 1;
        } else {
          next_ci = ci + 1;
        }

        bool near_middle = abs(ci - n/2) < 1;

        if (!near_middle) {
          // Overflows past the end of localColor / status, but safe.
          status[next_ci] = cyclesPerIndex;
          localColor[next_ci][part] = c;
          saveColor[next_ci][part] = saveColor[ci][part];
        }

        (*colors)[ci][part] = c;
      }

      if (s == 0) {
        // Dim light behind the Collide (Tracer) (towards saveColor)
        // TODO delta should be based on all 3 colors (
        int delta = saveColor[ci][part] - (*colors)[ci][part];
        delta = clamp(delta, -decayPerCycle, decayPerCycle);

        (*colors)[ci][part] = (*colors)[ci][part] + delta;
      }
    }
    status[ci] = 0;
  }
}
