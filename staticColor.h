#ifndef STATIC_COLOR_H
#define STATIC_COLOR_H

#include "effect.h"

class StaticColor: public Effect {
  public:
    void setupEffect() override;
    void iterate() override;

  private:
    int staticColor[3] = {};

    float brightness;
    float deriv;
    float threshold;
};

#endif /* STATIC_COLOR_H */
