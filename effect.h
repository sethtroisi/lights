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
    int status[100] = {};
    int localColor[100][3] = {};
    float floatColor[100][3] = {};
    int (*colors)[100][3];

    // Helper methods
    float distance3dScaled(int a[3], int b[3]);

    bool oneInX(int x);
    bool oneInX(float x);

    int randomInt(int a, int b);
    float randomFloat(); // [0 to 1]

    int clamp(int a, int min, int max);
    void setColor(int i, int r, int g, int b, int colors[][3]);

    int moveTowardsColor(int part, int steps, int colorA[], int colorB[]);

    void setColorsFromFloat(int minPartToShow);
};

#endif /* EFFECT_H */
