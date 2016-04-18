#include "effect.h"

class Tracer:  public Effect {
  public:
    void setupEffect(int colors[][3]) override;
    void iterate(int colors[][3]) override;

  private:
    bool oneInX(int x);
};
