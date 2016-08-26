#ifndef TRACER_H
#define TRACER_H

#include "effect.h"

class Tracer: public Effect {
  public:
    void setupEffect() override;
    void iterate() override;

  private:
    int cyclesPerIndex;
    int decayPerCycle;
    int saveColor[100][3];
};

#endif /* TRACER_H */
