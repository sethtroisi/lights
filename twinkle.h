#ifndef TWINKLE_H
#define TWINKLE_H

#include "effect.h"

class Twinkle: public Effect {
  public:
    void setupEffect() override;
    void iterate() override;

  private:
    int cyclesToNewColor;

    int twinkleRampUp;
    int twinkleRampDown;
    float twinklePercent;

    int status[100] = {};
    int twinkleColor[100][3] = {};
    int goalColorA[3] = {};
    int goalColorB[3] = {};

    void setGoalColor();
    void setRandomColor(int index);
};

#endif /* TWINKLE_H */
