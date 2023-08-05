#include "animationChain.h"

Animation* AnimationChain::currAnim() {
    return this->animations[this->playingAnimIndex];
}

void AnimationChain::update() {
    if (this->isActive) {
        bool isLast = (unsigned int)(this->playingAnimIndex + 1) >= this->animations.size();
        this->isActive = !(isLast && !this->currAnim()->isActive);

        if (!currAnim()->isActive) {
            if (!isLast) {
                this->playingAnimIndex++;
                this->currAnim()->start();
                this->isActive = true;
            } else {
                if (this->isLoop) {
                    this->start();
                }
            }
        }
        this->currAnim()->update();
    }
}

void AnimationChain::start() {
    this->playingAnimIndex = 0;
    this->isActive = true;
    if (this->currAnim()->pausedTime == 0) {
        this->currAnim()->start();
    } else {
        this->currAnim()->start();
        this->currAnim()->startTime = millis() - (this->currAnim()->pausedTime - this->currAnim()->startTime);
        this->currAnim()->pausedTime = 0;
    }
}

void AnimationChain::pause() {
    this->isActive = false;
    this->currAnim()->pausedTime = millis();
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