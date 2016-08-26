#ifndef ROTATE_H
#define ROTATE_H

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

#endif /* ROTATE_H */
