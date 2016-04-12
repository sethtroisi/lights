#include "effect.h"

class Sorter:  public Effect {
  public:
    void setupEffect(int colors[][3]);
    void iterate(int colors[][3]);

  private:
    int bubbleI, bubbleJ;

    void swapColors(int colors[][3], int i, int j);
    int randomInt(int a, int b);
};
