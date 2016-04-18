#include "effect.h"

class Sorter:  public Effect {
  public:
    void setupEffect();
    void iterate();

  private:
    int bubbleI, bubbleJ;

    void swapColors(int colors[][3], int i, int j);
    int randomInt(int a, int b);
};
