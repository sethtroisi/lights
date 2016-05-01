#include "effect.h"

class Mood: public Effect {
  public:
    void setupEffect() override;
    void iterate() override;

  private:
    int cyclesPerColor;

    float spread;
    float oddScaler;
    float movePercent;
    float decayRate;

    int goalIndex;
    int goalColor[3] = {};
};
