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
