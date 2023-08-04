#include "animo.h"

void Animo::advanceAnimations() {
    for (Animation* anim: this->animations) {
        if (anim->isActive) {
            if (anim->isActive) {
                anim->update();
            } else {
                if (anim->nextAnimation && anim->isLoop) {
                    anim = anim->nextAnimation;
                    anim->isLoop = true;
                    anim->start();
                } else {
                    delete anim;
                    anim = nullptr;
                }
            }
        }
    }
}

void Animo::startAnimation(Animation *animation) {
    for (u_int8_t i = 0; i < ANIMO_SIZE_OF_ANIMATION_ARRAY; i++) {
        if (!this->animations[i]) {
            this->animations[i] = animation;
            this->animations[i]->start();
            return;
        }
    }
}

void Animo::startLoopAnimation(Animation *animation) {
    animation->isLoop = true;
    startAnimation(animation);
}

void Animo::stopAllAnimations(boolean force) {
    for(u_int8_t i = 0; i < ANIMO_SIZE_OF_ANIMATION_ARRAY; i++) { 
        if (force) {
            delete this->animations[i];
            this->animations[i] = nullptr;
        } else {
            this->animations[i]->nextAnimation = nullptr;
        }
    }
}

void Animation::addAnimation() {
    this->animations.push_back(Animation(startValue, endValue, updateCallback, easingFunction));
}
