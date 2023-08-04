#include "animationChain.h"

Animation* AnimationChain::currAnim() {
    return this->animations[this->playingAnimIndex];
}

void AnimationChain::update() {
    if (this->isActive) {
        this->isActive = !(this->playingAnimIndex + 1 >= this->animations.size() && 
            !this->currAnim()->isActive);

        if (!currAnim()->isActive) {
            if (this->playingAnimIndex + 1 < this->animations.size()) {
                this->playingAnimIndex++;
                this->currAnim()->start();
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
        this->currAnim()->startTime = millis();
    } else {
        this->currAnim()->startTime = millis() - (this->currAnim()->pausedTime - this->currAnim()->startTime);
        this->currAnim()->pausedTime = 0;
    }
}

void AnimationChain::pause() {
    this->isActive = false;
    this->currAnim()->pausedTime = millis();
}

Animation* AnimationChain::addAnimation(unsigned long startTime, unsigned long duration, bool isLoop = false) {
    Animation animation = Animation(startTime, duration, isLoop);
    this->animations.push_back(&animation);
    return &animation;
}

void AnimationChain::removeAnimation(Animation* animation, bool allowChainToFinish = true, bool allowAnimationToFinish = true) {
    auto it = std::find_if(animations.begin(), animations.end(),
        [animation](const Animation& anim) {
            return &anim == animation;
        });

    if (it != animations.end()) {
        if (allowChainToFinish) {
            
        } else if (allowAnimationToFinish) {

        } else {
            animations.erase(it);
        }
    }
}