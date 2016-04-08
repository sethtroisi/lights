#include <algorithm>
#include <cstdlib>
#include <iostream>

using namespace std;

bool oneInX(int x) {
  return rand() % x == 0;
}


void tracer(int round, int colors[][3], int status[][3], int numLights) {
  if (oneInX(40)) {
    cout << "\tstarting tracer!" << endl;

    status[0][0] = 255 * oneInX(2);
    status[0][1] = 255 * oneInX(2);
    status[0][2] = 255 * oneInX(2);
  }

  for (int ci = numLights - 1; ci >= 0; ci--) {
    for (int part = 0; part < 3; part++) {
      if (status[ci][part]) {
        int s = status[ci][part];

        if (ci+1 < numLights) {
          status[ci+1][part] = s;
        }
        colors[ci][part] = s;
        status[ci][part] = 0;
      } else {
        colors[ci][part] = max(0, colors[ci][part] - 30);
      }
    }
  }
}
