#include <iostream>

#include "tracer.h"

using namespace std;


void Tracer::setupEffect() {
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
    setColor(i, 2 /* Red*/, 2 /* Green */, 2 /* Blue */, saveColor);
  }

  //////////// CONFIG ENDS HERE ////////////
};  

void Tracer::iterate() {
  if (oneInX(25 * cyclesPerIndex)) {

    status[0] = cyclesPerIndex;
    setColor(0, 255 * oneInX(2), 255 * oneInX(2), 255 * oneInX(2), localColor);
    cout << "\tstarting tracer: ";
    cout << localColor[0][0] << "," << localColor[0][1] << "," << localColor[0][2] << endl;
  }

  for (int ci = n - 1; ci >= 0; ci--) {
    int s = status[ci];
    if (s > 1) {
      status[ci] -= 1;
      continue;
    }

    for (int part = 0; part < 3; part++) {
      if (s == 1) {
        int c = localColor[ci][part];

        // Overflows past the end of localColor / status, but safe.
        status[ci+1] = cyclesPerIndex;
        localColor[ci+1][part] = c;

        (*colors)[ci][part] = c;
      }

      if (s == 0) {
        // Dim light behind the Tracer (towards saveColor)
        // TODO delta should be based on all 3 colors (
        int delta = saveColor[ci][part] - (*colors)[ci][part];
        delta = clamp(delta, -decayPerCycle, decayPerCycle);

        (*colors)[ci][part] = (*colors)[ci][part] + delta;
      }
    }
    status[ci] = 0;
  }
}
