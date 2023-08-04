#include "animationVariable.h"

void AnimationVariable::update(unsigned long time) {
    this->easingFunction(this, time);
    this->updateCallback(*this);
}