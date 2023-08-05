#include "animation.h"

void Animation::update() {
    if (this->isActive) {
        this->isActive = (millis() - this->startTime <= this->duration);

        if (this->isActive) {
            float time = float(millis() - this->startTime) / this->duration;
            for (AnimationVariable var: this->variables) {
                var.update(time);
            }
        } else {
            if (this->isLoop) {
                this->start();
            }
        }
    }
}

void Animation::start() {
    this->isActive = true;
    if (this->pausedTime == 0) {
        this->startTime = millis();
    } else {
        this->startTime = millis() - (this->pausedTime - this->startTime);
        this->pausedTime = 0;
    }
}

void Animation::pause() {
    this->isActive = false;
    this->pausedTime = millis();
}

AnimationVariable Animation::addVar(int startValue, int endValue, 
    VariableUpdateCallback updateCallback, EasingFunction easingFunction) {
    AnimationVariable variable = AnimationVariable(startValue, endValue, updateCallback, easingFunction);
    this->variables.push_back(variable);
    return variable;
}

void Animation::removeVar(AnimationVariable* variable) {
    auto it = std::find_if(variables.begin(), variables.end(),
        [variable](const AnimationVariable& var) {
            return &var == variable;
        });

    if (it != variables.end()) {
        variables.erase(it);
    }
}