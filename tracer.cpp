#include <algorithm>
#include <cstdlib>
#include <iostream>

#include "tracer.h"

using namespace std;




void Tracer::setupEffect(int colors[][3]) {
  for (int i = 0; i < n; i++) {
    status[i] = 0;
    localColor[i][0] = localColor[i][1] = localColor[i][2] = 0;
  }


  /////////// CONFIG STARTS HERE ///////////

  status[0] = 1;          // Start with an active "Trace"
  localColor[0][0] = 200; // color to "trace" (RED)

  for (int i = 0; i < n; i++) {
    setColor(i, 0 /* Red*/, 50 /* Green */, 100 /* Blue */, colors);
  }

  //////////// CONFIG ENDS HERE ////////////
};  

void Tracer::iterate(int colors[][3]) {
  if (oneInX(40)) {
    cout << "\tstarting tracer!" << endl;

    status[0] = 1;
    localColor[0][0] = 255 * oneInX(2);
    localColor[0][1] = 255 * oneInX(2);
    localColor[0][2] = 255 * oneInX(2);

    cout << localColor[0][2] << endl;
  }

  for (int ci = n - 1; ci >= 0; ci--) {
    int s = status[ci];
    for (int part = 0; part < 3; part++) {
      if (s) {
        int c = localColor[ci][part];

        if (ci+1 < n) {
          status[ci+1] = s;
          localColor[ci+1][part] = c;
        }

        colors[ci][part] = c;
      } else {
        // Dim light behind the Tracer
        colors[ci][part] = max(0, colors[ci][part] - 15);
      }
    }
    status[ci] = 0;
  }
// */
}

bool Tracer::oneInX(int x) {
  return rand() % x == 0;
}
