#include "animation.h"

void Animation::update() {
    if (this->isActive) {
        unsigned long currentTime = millis();
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

            if (this->isLoop) {
                this->start();
            } else {
                if (this->finishedCallback) {
                    this->finishedCallback();
                    this->isFinished = true;
                }
            }
        }
    }
}

void Animation::start() {
    this->isActive = true;
    this->startTime = this->pausedTime == 0
        ? millis()
        : millis() - (this->pausedTime - this->startTime);
    this->pausedTime = 0;
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

void Animation::setFinishedCallback(std::function<void()> finishedCallback) {
    this->finishedCallback = finishedCallback;
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