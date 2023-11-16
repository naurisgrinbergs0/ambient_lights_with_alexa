#include "animation.h"

void Animation::update() {
    unsigned long currentTime = millis();
    if (this->isActive) {
        // update each variable
        float time = float(currentTime - this->startTime) / this->duration;
        for (AnimationVariable& var : this->variables) {
            var.update(time > 1 ? 1 : time);
        }

        // check if the duration has been exceeded
        if (currentTime - this->startTime >= this->duration) {
            for (AnimationVariable& var : this->variables) {
                var.update(1);
            }
            this->isActive = false;

            // if the animation is looping, restart it
            if (this->isLoop) {
                this->start();
            }
            // trigger the finish callback if provided
            if (this->finishedCallback) {
                this->finishedCallback();
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

void Animation::addVar(int startValue, int endValue, 
    std::function<void(const AnimationVariable)> updateCallback, EasingFunction easingFunction) {
    AnimationVariable variable = AnimationVariable(startValue, endValue, updateCallback, easingFunction);
    this->variables.push_back(variable);
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