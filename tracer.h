#include "effect.h"

class Tracer:  public Effect {
  public:
    void setupEffect(int colors[][3]);
    void iterate(int colors[][3]);

  private:
    bool oneInX(int x);
};
