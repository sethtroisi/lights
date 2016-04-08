#include <chrono>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>

#include <wiringPi.h>

using namespace std;

#define NUM_LIGHTS 47
#define UPDATES_PER_SECOND 100
#define CYCLE_DELAY_US (1000000.0 / updatesPerSecond)
#define LATCH_TIME_US 800 // ~>280us works but safety margin is good

#define DIST_LEN 100
#define DIST_POW 1.1


void printDistribution(int counts[], int n, double power) {
  int total = 0;
  int maxCount = 1;
  for (int i = 0; i < n; i++) {
    total += counts[i];
    maxCount = max(maxCount, counts[i]);
  }

  int stars = 25;
  int countPerStar = max(1, maxCount / stars);

  int seen = 0;
  for (int i = 0; i < n; i++) {
    if (seen == 0 && counts[i] == 0)
      continue;

    if (seen == total)
      break;
    seen += counts[i];

    cout << left << setw(5) << (int) pow(power, i) << " : ";
    cout << left << setw(5) << counts[i] << " : ";
    cout << fixed << setprecision(1) << setw(4) << ((100.0 * counts[i]) / total) << "% : ";

    for (int s = 0; s < (counts[i] - 1) / countPerStar + 1; s++) {
      cout << "*";
    }
    cout << endl;
  }
}

int main(void) {
  setupLights();

  cout << "Hello to Lights Master!" << endl;


  int durationLogDist[DIST_LEN] = {};

  int colors[NUM_LIGHTS][3] = {};
  for (int ci = 0; ci < NUM_LIGHTS; ci++) {
      colors[ci][0] = 128;
      colors[ci][1] = 128;
      colors[ci][2] = 128;
  }

  for (int round = 0; round < 600 * updatesPerSecond; round++) {
    if (round % 100 == 0) {
      cout << "round: " << round << endl;
    }

    auto begin = chrono::high_resolution_clock::now();
    // RECORD INNER TIMING

    for (int ci = 0; ci < numLights; ci++) {
      colors[ci][0] = max(0, colors[ci][0] - 1);
      colors[ci][1] = max(0, colors[ci][1] - 1);
      colors[ci][2] = max(0, colors[ci][2] - 1);

      writeColor(colors[ci]);
    }

    // END RECORD INNER TIMING
    auto end = chrono::high_resolution_clock::now();
    int durationUS = chrono::duration_cast<chrono::microseconds>(end-begin).count();
    int durLog = ceil(log(durationUS) / log(DIST_POW));
    //cout << "us total: " << duration << " (" << durLog << ")" << endl;
    durationLogDist[durLog] += 1;

    delayMicroseconds(max(LATCH_TIME_US, cycleDelayUS - durationUS));
  }

  printDistribution(durationLogDist, distLen, distPow);
 
  return 0;
}
