#include <cassert>
#include <iostream>

#include "twinkle.h"

using namespace std;

void Twinkle::setGoalColor() {
  // Save A to B.
  goalColorB[0] = goalColorA[0];
  goalColorB[1] = goalColorA[1];
  goalColorB[2] = goalColorA[2];

  while (true) {
    // Create new Goal Color.
    goalColorA[0] = randomInt(140,200);
    goalColorA[1] = randomInt(10,80);
    goalColorA[2] = randomInt(0,20);

    // shuffle parts of color.
    swap(goalColorA[2], goalColorA[randomInt(0,2)]);
    swap(goalColorA[1], goalColorA[randomInt(0,1)]);

    for (int p = 0; p < 3; p++) {
      cout << "\t" << "RBG"[p] << " " << goalColorB[p] << " vs " << goalColorA[p] << endl;
    }

    float d = distance3dScaled(goalColorA, goalColorB);
    cout << "\t\t" << d << endl;

    if ((d > .45) || (d > .05 && d < .15) ) {
      break;
    }
  }
}


void Twinkle::setRandomColor(int index) {
  // Choose a color between goalColorA and goalColorB biased based on iter.
  // 0-10% of one, 90-100% of other

  float large = 0.9 + 0.1 * randomFloat();
  float small = 1 - large;

  float amountA, amountB;
  if (randomFloat() < (1.0 * iter / cyclesToNewColor)) {
    // More A than B.
    amountA = large;
    amountB = small;
  } else {
    // More B than A.
    amountA = small;
    amountB = large;
  }

  for (int part = 0; part < 3; part++) {
    twinkleColor[index][part] = amountA * goalColorA[part] + amountB * goalColorB[part];
  }
};


void Twinkle::setupEffect() {
  /////////// CONFIG STARTS HERE ///////////

  cyclesToNewColor = 12 * 50; // Roughly twenty seconds.

  twinkleRampUp = 30;
  twinkleRampDown = 35;
  twinklePercent = .13;

  //////////// CONFIG ENDS HERE ////////////
  twinklePercent *= 1.4 * ((twinkleRampUp + twinkleRampDown)) / 50.0 / 50.0;

  setGoalColor();

  cout << "\t\ttwinkling towards ";
  cout << goalColorA[0] << ", " << goalColorA[1] << ", " << goalColorA[2] << endl;

  setColor(1, goalColorA[0], goalColorA[1], goalColorA[2], *colors);
  setColor(2, goalColorB[0], goalColorB[1], goalColorB[2], *colors);
};  





void Twinkle::iterate() {
  iter++;

  if (iter % cyclesToNewColor == 0) {
    setupEffect();
    iter = 0;
  }

  for (int ci = 3; ci < n; ci++) {
    if (randomFloat() < twinklePercent) {
      if (status[ci] == 0) {
        setRandomColor(ci);
        status[ci] = twinkleRampUp + twinkleRampDown;
      }
    }

    int twinkle = status[ci];
    float percent;

    if (twinkle >= twinkleRampDown) {
      percent = 1.0 * (twinkleRampUp - (twinkle - twinkleRampDown)) / twinkleRampUp;
    } else {
      percent = 1.0 * twinkle / twinkleRampDown;
    }

    for (int part = 0; part < 3; part++) {
      int goal = twinkleColor[ci][part];

      (*colors)[ci][part] = goal * percent;
    }

    if (status[ci] > 0) {
      status[ci] -= 1;
    }
  }
}
