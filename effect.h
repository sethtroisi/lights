#ifndef EFFECT_H
#define EFFECT_H

class Effect
{
  protected:
    int n;
    int iter;
    int status[100][3];

  public:
    void setNumLights(int a) { n = a; };

    virtual void setupEffect(int colors[][3])=0;

    virtual void iterate(int colors[][3])=0;
};

#endif /* EFFECT_H */
