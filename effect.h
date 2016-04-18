#ifndef EFFECT_H
#define EFFECT_H

class Effect
{
  public:
    virtual ~Effect() {}

    void setNumLights(int a);

    virtual void setupEffect(int colors[][3]) = 0;
    virtual void iterate(int colors[][3]) = 0;

  protected:
    int n;
    int iter;
    int status[100];
    int localColor[100][3];

    // Helper methods
    int clamp(int a, int min, int max);
    int setColor(int i, int r, int g, int b, int colors[][3]);
};

#endif /* EFFECT_H */
