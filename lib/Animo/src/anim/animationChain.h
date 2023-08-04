#pragma once

#include <Arduino.h>
#include "animation.h"
#include "../constants.h"

class AnimationChain {
protected:
    std::vector<Animation*> animations;

    Animation* currAnim();
    
public:
    bool isLoop = false;
    bool isActive = false;
    u_int8_t playingAnimIndex = 0;
    std::vector<Animation*> animations;

    AnimationChain(bool isLoop = false): isLoop(isLoop) {};

    void start();
    void pause();
    void update();

    Animation* addAnimation(unsigned long startTime, unsigned long duration, bool isLoop = false);
    void removeAnimation(Animation* animation, bool allowChainToFinish = true, bool allowAnimationToFinish = true);
};
