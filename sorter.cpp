#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <iostream>

#include "sorter.h"

using namespace std;

int Sorter::randomInt(int a, int b) {
  // inclusive over [a, b]
  float r = (float)rand() / (float)RAND_MAX;
  return a + r * (b - a + 1);
}

void Sorter::setupEffect(int colors[][3]) {
  // Build random colors and store their "true" sort order in status.

  // TODO build colors starting from middle

  cout << "\tStarting sorter!" << endl;

  int curColor[3] = {
    randomInt(235, 255),
    randomInt(0, 20),
    randomInt(0, 20),
  };

  int goalColors[2][3] = {
    {0,255,0},
    {0,0,255}
  };

  // The approx amount each light component should change per light.
  // So that it goes from Red to Green to Blue across the full chain.
  int deltaPer = ceil(255.0 / (n / 2.0));
  int threshold = 10 + deltaPer;

  for (int i = 0; i < n; i++) {
    status[i] = i;
    int goalColor = (2*i) / n;

    for (int part = 0; part < 3; part++) {
      colors[i][part] = curColor[part];

      int delta = goalColors[goalColor][part] - curColor[part];
      // convert delta to one of {-deltaPer, 0, deltaPer}
      int shift = deltaPer * ((delta > threshold) - (delta < threshold));

      curColor[part] += shift + randomInt(-10, 10);
      curColor[part] = clamp(curColor[part], 0, 255);
    }
  }

  // Randomize the array
  for (int i = 0; i <= n-2; i++) {
    int j = randomInt(0, n - i - 1);
    swapColors(colors, i, i + j);
  }

  iter = 0;
  bubbleI = 0;
  bubbleJ = 0;
};  

void Sorter::iterate(int colors[][3]) {
  iter++;

  if (iter < 100) {
    return;
  }

  // for (int i = 0; i < n-1; i++)
  //  for (int j = i; j < n-1; j++)
  //    maybeSwap(colors, i, j); 

  if (bubbleI < n-1 && bubbleJ < n-1) {
    // cheat and look at status to find "real" order. 
    if (status[bubbleI] < status[bubbleJ]) {
      swapColors(colors, bubbleI, bubbleJ);
    }
  }

  bubbleJ++;
  if (bubbleJ >= n-1) {
    bubbleI++;
    bubbleJ = bubbleI;
//    cout << "\tbubbleI: " << bubbleI << endl;

    if (bubbleI >= n-1) {
      // wait a while at the end
      if (bubbleI - (n-1) > 100) {
        setupEffect(colors);
      }
    }
  }
}

void Sorter::swapColors(int colors[][3], int i, int j) {
//  printf("\tswapping %d (%d) and %d (%d)\n", i, status[i], j, status[j]);
  for (int part = 0; part < 3; part++) {
    swap(colors[i][part], colors[j][part]);
  }

  swap(status[i], status[j]);
}
