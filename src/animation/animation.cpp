#include "animation/animation.h"

/// TODO: Move duration from Variable class to Animation class
/// there is no need for it inside variable, it would make more
/// sense if it was stored in animation itself because all the
/// variables of that animation will have the same duration
/// When calling the easing function - could pass a time value separately

void Animation::update() {
    bool isActive = false;
    for (u_int8_t i = 0; i < NUM_OF_VARIABLES; i++) {
        if (millis() - this->variables[i].startTime <= this->variables[i].duration) {
            isActive = true;
            break;
        }
    }
    if (!isActive) {
        this->isActive = false;
        return;
    }

    for (u_int8_t i = 0; i < NUM_OF_VARIABLES; i++) {
        this->variables[i].update();
    }
    if (this->updateCallback) {
        this->updateCallback(this->variables);
    }
}

void Animation::setNext(Animation *nextAnimation) {
    this->nextAnimation = nextAnimation;
}

void Animation::start() {
    this->isActive = true;
    for (u_int8_t i = 0; i < NUM_OF_VARIABLES; i++) {
        this->variables[i].reset();
    }
}