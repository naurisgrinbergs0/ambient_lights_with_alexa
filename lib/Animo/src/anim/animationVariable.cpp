#include "animationVariable.h"

void AnimationVariable::update(float time) {
    this->easingFunction(this, time);
    this->updateCallback(*this);
}