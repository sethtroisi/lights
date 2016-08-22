#ifndef EFFECT_CONTROLLER_H
#define EFFECT_CONTROLLER_H

#include <memory>

#include "effect.h"

#define CYCLE_DELAY_US (1000000 / UPDATES_PER_SECOND)
#define APPROX_WRITE_DELAY_US (NUM_LIGHTS * 24 * WRITE_DELAY_US * 2)

class EffectController
{
  public:
    virtual ~EffectController() {}

    void setupEffectController(int numLights, int updatesPerSecond, int latchTimeUS);
    void run();

  private:
    bool hasNewEffect();
    bool loadEffect();

    void runEffect();

    // The effect currently running (or to be run)
    std::unique_ptr<Effect> effect_;

    // random interal stats
    int round_;
    time_t last_file_update_;

    // params
    int showTime_;
    int numLights_;
    int updatesPerSecond_;
    int latchTimeUS_;

    // derived params
    int USPerIter_;

};

#endif /* EFFECT_CONTROLLER_H */
