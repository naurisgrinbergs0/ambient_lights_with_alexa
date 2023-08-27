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
    std::function<void()> finishedCallback;

    ~AnimationChain();
    AnimationChain(bool isLoop = false, std::function<void()> finishedCallback = nullptr): 
        isLoop(isLoop), finishedCallback(finishedCallback) {};

    void start();
    void pause();
    void update();

    Animation* addAnimation(unsigned long duration);
    void removeAnimation(Animation* animation, bool allowToFinish = true);
};
