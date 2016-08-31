#ifndef DANGER_H
#define DANGER_H

#include "effect.h"

class Danger: public Effect {
  public:
    void setupEffect() override;
    void iterate() override;

  private:
    int numFlashes;
    int flashCycleDuration;

    int numTracers;
    int tracerCycleDuration;
    int tracerLength;

    int dangerColor[3] = {};

    int showCycles;
};

#endif /* DANGER_H */
