#include <algorithm>
#include <cmath>
#include <cstdlib>
#include "effect.h"

using namespace std;


void Effect::setLights(int a, int (*colorPointer)[100][3]) {
  n = a;
  colors = colorPointer;
}

int Effect::clamp(int a, int minV, int maxV) {
  return a<minV ? minV : (a>maxV ? maxV: a);
}

float Effect::distance3dScaled(int a[3], int b[3]) {
  // TODO use something different later like HSL
  float dist = 0;
  int largest = 1;
  for (int part = 0; part < 3; part++) {
    int delta = a[part] - b[part];
    dist += delta * delta;
    largest = max(max(largest, a[part]), b[part]);
  }

  return 1 - (dist / (3.0 * largest * largest));
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


void Effect::setColorsFromFloat(int minToShow) {
  for (int i = 0; i < n; i++) {
    float maxPart = std::max(std::max(
        floatColor[i][0],
        floatColor[i][1]),
        floatColor[i][2]);


    for (int part = 0; part < 3; part++) {
      float c = floatColor[i][part];

      if (maxPart >= minToShow) {
        (*colors)[i][part] = clamp(c, 0, 255);
      } else {
        (*colors)[i][part] = 0;
      }
    }
  }
}

