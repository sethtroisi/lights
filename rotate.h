#include "effect.h"

class Rotate : public Effect {
  public:
    void setupEffect() override;
    void iterate() override;

  private:
    void setWheelColor(int i, int wp);

    int cyclesPerPos;
    int wheelPosPerIndex;

    int wheelPos;
};
