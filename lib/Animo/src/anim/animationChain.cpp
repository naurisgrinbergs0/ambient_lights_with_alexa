#include "animationChain.h"

AnimationChain::~AnimationChain() {
    for(Animation* anim: this->animations) {
        delete anim;
    }
}

Animation* AnimationChain::currAnim() {
    return this->animations[this->playingAnimIndex];
}

void AnimationChain::update() {
    if (this->isActive) {
        bool isLast = (unsigned int)(this->playingAnimIndex + 1) >= this->animations.size();

        if (currAnim()->isFinished) {
            if (!isLast) {
                this->playingAnimIndex++;
                this->currAnim()->start();
            } else {
                if (this->isLoop) {
                    this->start();
                } else {
                    if (this->finishedCallback) {
                        this->finishedCallback();
                        this->isFinished = true;
                    }
                }
            }
        }
        this->currAnim()->update();
    }
}

void AnimationChain::start() {
    this->playingAnimIndex = 0;
    this->isActive = true;

    this->currAnim()->start();
    this->currAnim()->pausedTime = 0;
}

void AnimationChain::pause() {
    this->isActive = false;
    this->currAnim()->pause();
}

Animation* AnimationChain::addAnimation(unsigned long duration) {
    Animation* animation = new Animation(duration, false);
    this->animations.push_back(animation);
    return animation;
}

void AnimationChain::removeAnimation(Animation* animation, bool allowToFinish) {
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