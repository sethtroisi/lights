#ifndef EFFECT_CONTROLLER_H
#define EFFECT_CONTROLLER_H

#include <vector>

#define CYCLE_DELAY_US (1000000 / UPDATES_PER_SECOND)
#define APPROX_WRITE_DELAY_US (NUM_LIGHTS * 24 * WRITE_DELAY_US * 2)

class EffectController
{
  public:
    virtual ~EffectController() {}

    void setupEffectController(int showTime, int numLights, int updatesPerSecond, int latchTimeUS);
    void run();

  private:
    // params
    int showTime_;
    int numLights_;
    int updatesPerSecond_;
    int latchTimeUS_;

    // derived params
    int USPerIter_;

    // internals
//    vector<Effect> effects_;
};

#endif /* EFFECT_CONTROLLER_H */
