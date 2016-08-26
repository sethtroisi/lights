#ifndef MOOD_H
#define MOOD_H

#include "effect.h"

class Mood: public Effect {
  public:
    void setupEffect() override;
    void iterate() override;

  private:
    int cyclesPerColor;

    float spread;
    float effectRate;
    float decayRate;

    int goalIndex;
    int goalColor[3] = {};
};

#endif /* MOOD_H */
