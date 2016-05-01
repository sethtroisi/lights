#include <algorithm>
#include <cmath>
#include <cstdlib>
#include "effect.h"


void Effect::setLights(int a, int (*colorPointer)[100][3]) {
  n = a;
  colors = colorPointer;
}

int Effect::clamp(int a, int min, int max) {
  return a<min ? min : (a>max ? max: a);
}

int Effect::setColor(int i, int r, int g, int b, int colors[][3]) {
  colors[i][0] = r;
  colors[i][1] = g;
  colors[i][2] = b;
}

bool Effect::oneInX(int x) {
  // FIXME not perfect because of rand() not being uniform on MOD X.
  return (x == 0) || rand() % x == 0;
}

bool Effect::oneInX(float x) {
  return (x < 0.001) || (randomFloat() * x < 1);
}

float Effect::randomFloat() {
  return (float)rand() / (float)RAND_MAX;
}

int Effect::randomInt(int a, int b) {
  // inclusive over [a, b]
  int delta = abs(b - a) + 1;
  float r = (float)rand() / (float)RAND_MAX;
  int c = delta * r;
  return a + c;
}

