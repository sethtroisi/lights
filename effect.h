#ifndef EFFECT_H
#define EFFECT_H


class Effect
{
  public:
    virtual ~Effect() {}

    void setLights(int a, int (*colors)[100][3]);

    virtual void setupEffect() = 0;
    virtual void iterate() = 0;

  protected:
    int n;
    int iter;
    int status[100];
    int localColor[100][3];
    int (*colors)[100][3];

    // Helper methods
    int clamp(int a, int min, int max);
    int setColor(int i, int r, int g, int b, int colors[][3]);
};

#endif /* EFFECT_H */
