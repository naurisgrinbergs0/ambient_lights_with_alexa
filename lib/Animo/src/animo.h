#pragma once

#include "anim/animationVariable.h"
#include "anim/animation.h"
#include "anim/animationChain.h"
#include "constants.h"

class Animo {
private:
    std::vector<Animation*> animations;
    std::vector<AnimationChain*> animationChains;

public:
    void advanceAnimations();
    void removeAllAnimations(bool allowToFinish = true);

    Animation* Animation::addAnimation(unsigned long startTime, unsigned long duration, bool isLoop = false);
    void Animation::removeAnimation(Animation* animation, bool allowToFinish = true);

    AnimationChain* Animation::addAnimationChain(Animation animationChain[], bool isLoop = false);
    void Animation::removeAnimationChain(AnimationChain* animation, bool allowToFinish = true);
};
