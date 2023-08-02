#include <Arduino.h>
#include "animationVariable.h"

void AnimationVariable::reset() {
    this->startTime = millis();
}

void AnimationVariable::update() {
    if (this->easingFunction) {
        this->easingFunction(this);
    } 
}