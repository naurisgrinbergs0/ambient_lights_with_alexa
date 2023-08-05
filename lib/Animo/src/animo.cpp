#include "animo.h"

void Animo::advanceAnimations() {
    for (Animation* anim: this->animations) {
        anim->update();
    }

    for (AnimationChain* ch: this->animationChains) {
        ch->update();
    }
}

void Animo::removeAllAnimations(bool allowToFinish) {
    if (allowToFinish) {

    } else {
        this-> animations.clear();
    }
}

Animation* Animo::addAnimation(unsigned long duration, bool isLoop) {
    Animation* animation = new Animation(duration, isLoop);
    this->animations.push_back(animation);
    return animation;
}

void Animo::removeAnimation(Animation* animation, bool allowToFinish) {
    auto it = std::find_if(animations.begin(), animations.end(),
        [animation](const Animation* anim) {
            return anim == animation;
        });

    if (it != animations.end()) {
        if (allowToFinish) {

        } else {
            animations.erase(it);
            delete animation;
        }
    }
}

AnimationChain* Animo::addAnimationChain(bool isLoop) {
    AnimationChain* chain = new AnimationChain(isLoop);
    this->animationChains.push_back(chain);
    return chain;
}

void Animo::removeAnimationChain(AnimationChain* chain, bool allowChainToFinish, bool allowAnimationToFinish) {
    auto it = std::find_if(animationChains.begin(), animationChains.end(),
        [chain](const AnimationChain* ch) {
            return ch == chain;
        });

    if (it != animationChains.end()) {
        if (allowChainToFinish) {
                   
        } else if (allowAnimationToFinish) {

        } else {
            animationChains.erase(it);
            delete chain;
        }
    }
}