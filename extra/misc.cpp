#include <chrono>
#include <cmath>
#include <iomanip>
#include <iostream>

#include "misc.h"

using namespace std;

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

int clamp(int x, int minV, int maxV) {
  return x < minV ? minV : (x > maxV ? maxV : x);
}


int calcBin(int amount) {
  int bin = ceil(log(amount) / log(DIST_POW));
  return clamp(bin, 0, DIST_LEN-1);
}


//  int durationLogDist[DIST_LEN] = {};
//    auto begin = chrono::high_resolution_clock::now();
    // RECORD INNER TIMING

//  auto end = chrono::high_resolution_clock::now();
//    int durationUS = chrono::duration_cast<chrono::microseconds>(end-begin).count();
//    int durLog = ceil(log(durationUS) / log(DIST_POW));
    //cout << "us total: " << duration << " (" << durLog << ")" << endl;
//    durationLogDist[durLog] += 1;

  // Print write timing info
//  printDistribution(durationLogDist, DIST_LEN, DIST_POW);
