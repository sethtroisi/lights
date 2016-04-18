#ifndef EFFECT_H
#define EFFECT_H

class Effect
{
  protected:
    int n;
    int iter;
    int status[100];
    int localColor[100][3];

  public:
    virtual ~Effect() {}

    void setNumLights(int a) {
      n = a;
    }

    int clamp(int a, int min, int max) {
      return a<min ? min : (a>max ? max: a);
    }

    virtual void setupEffect(int colors[][3]) = 0;

    virtual void iterate(int colors[][3]) = 0;
};

#endif /* EFFECT_H */
