#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <iostream>

#include "sorter.h"

using namespace std;

void Sorter::buildSortColors() {
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
      (*colors)[i][part] = curColor[part];

      int delta = goalColors[goalColor][part] - curColor[part];
      // convert delta to one of {-deltaPer, 0, deltaPer}
      int shift = deltaPer * ((delta > threshold) - (delta < threshold));

      curColor[part] += shift + randomInt(-20, 20);
      curColor[part] = clamp(curColor[part], 0, 255);
    }
  }
}

void Sorter::setupEffect() {
  // Build random colors and store their "true" sort order in status.
  // Build an rainbow of red, blue, green colors (pre sorted) in colors.
  buildSortColors();

  // Randomize the color's brightness.
  for (int i = 0; i < n; i++) {
    float brightness = 0.25 + 0.50 * randomFloat();

    for (int part = 0; part < 3; part++) {
      (*colors)[i][part] = clamp(brightness * (*colors)[i][part], 0, 255);
    }
  }

  // Randomize the color's position.
  for (int i = 0; i <= n-2; i++) {
    int j = randomInt(0, n - i - 1);
    swapColors(*colors, i, i + j);
  }

  iter = 0;
  indexI = 0;
  indexJ = 0;
};  

void Sorter::iterate() {
  iter++;

  if (iter < 100) {
    return;
  }

  ///*
  // Insertion sort

  // for (int i = 1; i < n; i++) {
  //  int j = i
  //  while (j > 0 and A[j-1] > A[j]) {
  //      swapColors(j-1, j);
  //  }
  // }

  // Insertion is fairly fast
  if (iter % 2 != 0) {
     return;
  }

  if (indexI >= n-1) {
    indexI++;
    // wait a while at the end
    if (indexI - (n-1) > 100) {
      setupEffect();
    }
  } else {
    if (indexJ == 0 || (status[indexJ - 1] < status[indexJ])) {
      indexI++;
      indexJ = indexI;
    } else {
      swapColors(*colors, indexJ - 1, indexJ);
      indexJ--;
    }
  }
  // */

  /*
  // Bubble sort

  // for (int i = 0; i < n-1; i++)
  //  for (int j = i; j < n-1; j++)
  //    maybeSwap(*colors, i, j);
  if (indexI < n-1 && indexJ < n-1) {
    // cheat and look at status to find "real" order. 
    if (status[indexI] < status[indexJ]) {
      swapColors(*colors, indexI, indexJ);
    }
  }

  indexJ++;
  if (indexJ >= n-1) {
    indexI++;
    indexJ = indexI;
//    cout << "\tindexI: " << indexI << endl;

    if (indexI >= n-1) {
      // wait a while at the end
      if (indexI - (n-1) > 100) {
        setupEffect();
      }
    }
  }
  // */
}

void Sorter::swapColors(int colors[][3], int i, int j) {
//  printf("\tswapping %d (%d) and %d (%d)\n", i, status[i], j, status[j]);
  for (int part = 0; part < 3; part++) {
    swap(colors[i][part], colors[j][part]);
  }

  swap(status[i], status[j]);
}
