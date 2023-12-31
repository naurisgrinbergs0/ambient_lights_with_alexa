#include "animo.h"

Animo::~Animo() {
    for (Animation* anim: this->animations) {
        delete anim;
    }

    for (AnimationChain* ch: this->animationChains) {
        delete ch;
    }
}


void Animo::advanceAnimations() {
    for (Animation* anim: this->animations) {
        if (anim->isActive) {
            anim->update();
        }
        if (anim->isFinished) {
            this->removeAnimation(anim, false);
        }
    }

    for (AnimationChain* ch: this->animationChains) {
        if (ch->isActive) {
            ch->update();
        } 
        if (ch->isFinished) {
            this->removeAnimationChain(ch, false);
        }
    }
}

void Animo::removeAllAnimations(bool allowToFinish) {
    if (allowToFinish) {

    } else {
        for(Animation* anim : this->animations) {
            delete anim;
        }
        this->animations.clear();
    }
}

void Animo::removeAllAnimationChains(bool allowToFinish) {
    if (allowToFinish) {

    } else {
        for(AnimationChain* ch : this->animationChains) {
            delete ch;
        }
        this->animationChains.clear();
    }
}


Animation* Animo::addAnimation(unsigned long duration, bool isLoop) {
    Animation* animation = new Animation(duration, isLoop);
    this->animations.push_back(animation);
    return animation;
}

AnimationChain* Animo::addAnimationChain(bool isLoop, std::function<void()> finishedCallback) {
    AnimationChain* chain = new AnimationChain(isLoop, finishedCallback);
    this->animationChains.push_back(chain);
    return chain;
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