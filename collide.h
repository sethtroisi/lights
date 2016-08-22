#include "effect.h"

class Collide: public Effect {
  public:
    void setupEffect() override;
    void iterate() override;

  private:
    int cyclesPerIndex;
    int decayPerCycle;
    int saveColor[100][3];
};
