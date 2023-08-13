#pragma once

#include <Arduino.h>
#include "animation.h"

class AnimationChain {
private:
    std::vector<Animation*> animations;

    Animation* currAnim();
    
public:
    bool isLoop = false;
    bool isActive = false;
    u_int8_t playingAnimIndex = 0;

    ~AnimationChain();
    AnimationChain(bool isLoop = false): isLoop(isLoop) {};

    void start();
    void pause();
    void update();

    Animation* addAnimation(unsigned long duration);
    void removeAnimation(Animation* animation, bool allowToFinish = true);
};
