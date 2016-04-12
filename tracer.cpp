#include <algorithm>
#include <cstdlib>
#include <iostream>

#include "tracer.h"

using namespace std;

void Tracer::setupEffect(int colors[][3]) {
  for (int i = 0; i < n; i++) {
    status[i][0] = status[i][1] = status[i][2] = 0;
  }
  status[0][1] = 100;
};  

void Tracer::iterate(int colors[][3]) {
  if (oneInX(40)) {
    cout << "\tstarting tracer!" << endl;

    status[0][0] = 255 * oneInX(2);
    status[0][1] = 255 * oneInX(2);
    status[0][2] = 255 * oneInX(2);
  }

  for (int ci = n - 1; ci >= 0; ci--) {
    for (int part = 0; part < 3; part++) {
      if (status[ci][part]) {
        int s = status[ci][part];

        if (ci+1 < n) {
          status[ci+1][part] = s;
        }
        colors[ci][part] = s;
        status[ci][part] = 0;
      } else {
        // Dim light behind the Tracer
        colors[ci][part] = max(0, colors[ci][part] - 15);
      }
    }
  }
// */
}

bool Tracer::oneInX(int x) {
  return rand() % x == 0;
}
