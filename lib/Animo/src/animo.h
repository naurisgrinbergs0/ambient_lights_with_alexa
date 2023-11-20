#pragma once

#include "anim/animationVariable.h"
#include "anim/easingFunctions.h"
#include "anim/animation.h"
#include "anim/animationChain.h"

#define ANIMO_LINEAR_EASING reinterpret_cast<EasingFunction>(linearEasing)
#define ANIMO_QUADRATIC_EASING reinterpret_cast<EasingFunction>(quadraticEasing)
#define ANIMO_CUBIC_EASING reinterpret_cast<EasingFunction>(cubicEasing)
#define ANIMO_SIGMOID_EASING reinterpret_cast<EasingFunction>(sigmoidEasing)
#define ANIMO_FAST_SIGMOID_EASING reinterpret_cast<EasingFunction>(fastSigmoidEasing)

class Animo {
private:
    std::vector<Animation*> animations;
    std::vector<AnimationChain*> animationChains;

public:
    ~Animo();

    void advanceAnimations();
    void removeAllAnimations(bool allowToFinish = true);
    void removeAllAnimationChains(bool allowToFinish = true);

    Animation* addAnimation(unsigned long duration, bool isLoop = false);
    void removeAnimation(Animation* animation, bool allowToFinish = true);

    AnimationChain* addAnimationChain(bool isLoop = false, std::function<void()> finishedCallback = nullptr);
    void removeAnimationChain(AnimationChain* animation, bool allowChainToFinish = true, bool allowAnimationToFinish = true);
};
