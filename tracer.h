#include "effect.h"

class Tracer:  public Effect {
  public:
    void setupEffect() override;
    void iterate() override;

  private:
    bool oneInX(int x);
};
