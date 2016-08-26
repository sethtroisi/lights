#ifndef BUBBLE_H
#define BUBBLE_H

#include "effect.h"

class Bubble: public Effect {
  public:
    void setupEffect() override;
    void iterate() override;

  private:
    int cyclesPerColor;

    float spread;
    float effectRate;
    float decayRate;

    static const int bubble_count = 10;
    int bubble_color[10][3];
    int bubble_index[10];
    float bubble_veloc[10];
};

#endif /* BUBBLE_H */
