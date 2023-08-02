#include "animation/animator.h"

void Animator::advanceAnimations() {
    for (u_int8_t i = 0; i < NUM_OF_ANIMATIONS; i++) {
        if (this->animations[i]) {
            if (this->animations[i]->isActive) {
                this->animations[i]->update();
            } else {
                if (this->animations[i]->nextAnimation && this->animations[i]->isLoop) {
                    this->animations[i] = this->animations[i]->nextAnimation;
                    this->animations[i]->isLoop = true;
                    this->animations[i]->start();
                } else {
                    delete this->animations[i];
                    this->animations[i] = nullptr;
                }
            }
        }
    }
}

void Animator::startAnimation(Animation *animation) {
    for (u_int8_t i = 0; i < NUM_OF_ANIMATIONS; i++) {
        if (!this->animations[i]) {
            this->animations[i] = animation;
            this->animations[i]->start();
            return;
        }
    }
}

void Animator::startLoopAnimation(Animation *animation) {
    animation->isLoop = true;
    startAnimation(animation);
}

void Animator::forceStopAnimations() {
    for(u_int8_t i = 0; i < NUM_OF_ANIMATIONS; i++) { 
        delete this->animations[i];
        this->animations[i] = nullptr;
    }
}

bool Animator::getIsActive() {
    for (u_int8_t i = 0; i < NUM_OF_VARIABLES; i++) {
        if (this->animations[i]) {
            if (this->animations[i]->isActive) {
                return true;
            }
        }
    }
    return false;
}


Animator* Animator::getInstance() {
    if (!Animator::instance) {
        Animator::instance = new Animator();
    }
    return Animator::instance;
}