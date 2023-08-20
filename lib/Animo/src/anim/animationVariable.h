#pragma once

#include <Arduino.h>
#include <functional>

struct AnimationVariable;
typedef void (*EasingFunction) (const AnimationVariable *variable, float time);

struct AnimationVariable {
    int startValue = 0;
    int endValue = 0;
    int value = 0;
    std::function<void(const AnimationVariable)> updateCallback = nullptr;

    EasingFunction easingFunction = nullptr;

    AnimationVariable(int startValue, int endValue, std::function<void(const AnimationVariable)> updateCallback, EasingFunction easingFunction):
        startValue(startValue), endValue(endValue), updateCallback(updateCallback), easingFunction(easingFunction) {};

    void update(float time);
};
