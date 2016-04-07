#include <chrono>
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>

#include <wiringPi.h>

using namespace std;

#define DATA_PORT 9
#define CLOCK_PORT 8

#define WRITE_DELAY_US 5

void writeBit(bool bit) {
    digitalWrite (DATA_PORT, bit);     // data
    delayMicroseconds(WRITE_DELAY_US);

    digitalWrite (CLOCK_PORT, 1);       // CLK up
    delayMicroseconds(WRITE_DELAY_US);

    digitalWrite (CLOCK_PORT, 0);       // CLK down
    delayMicroseconds(WRITE_DELAY_US);
}

void writeByte(int num) {
    assert (num >= 0);
    assert (num <= 255);

    for (int bit = 128; bit > 0; bit >>= 1) {
        writeBit((num & bit) > 0);
    }
}

void writeColor(int color[]) {
    writeByte(color[0]);
    writeByte(color[1]);
    writeByte(color[2]);
}

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

void setup(void) {
  // Give program higher priority to affect more real timeness.
  piHiPri(10);

  if (wiringPiSetup () == -1) {
    cout << "wiringPiSetup failed" << endl;
    exit;
  }

  pinMode (CLOCK_PORT, OUTPUT);
  pinMode (DATA_PORT, OUTPUT);

  srand(time(0));
}

 
int main(void) {

  setup();

  cout << "Hello world!" << endl;

  const int distLen = 100;
  const double distPow = 1.1;
  int durationLogDist[distLen] = {};

  for (int round = 0; round < 1114250; round++) {
    if (round % 100 == 0) {
      cout << "round: " << round << endl;
    }

    auto begin = chrono::high_resolution_clock::now();
    // RECORD INNER TIMING


    int colors[100][3] = {};
    for (int ci = 0; ci < 7; ci++) {
      colors[ci][0] = 0;
      colors[ci][1] = 0;
      colors[ci][2] = 0;
      colors[ci][0] = round % 256;
      colors[ci][1] = round % 256;
      colors[ci][2] = round % 256;
      writeColor(colors[ci]);
    }


    // END RECORD INNER TIMING
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(end-begin).count();

    int durLog = ceil(log(duration / 1000) / log(distPow));
    //cout << "us total: " << duration / 1000 << " (" << durLog << ")" << endl;
    durationLogDist[durLog] += 1;

    delayMicroseconds(830);
    delay(10);
  }

  cout << "program finished" << endl;
  cout << endl;

  printDistribution(durationLogDist, distLen, distPow);
 
  return 0;
}


// CAN ONLY WRITE BLUE TO 5th LED!!!!
// DELAY LATCH ~280us = .28ms
