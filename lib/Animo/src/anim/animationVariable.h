#pragma once

#include <Arduino.h>

struct AnimationVariable;
typedef void (*VariableUpdateCallback) (const AnimationVariable variable);
typedef void (*EasingFunction) (const AnimationVariable *variable, float time);

struct AnimationVariable {
    int startValue = 0;
    int endValue = 0;
    int value = 0;
    VariableUpdateCallback updateCallback = nullptr;
    EasingFunction easingFunction/* = ANIMO_LINEAR_EASING*/;

    AnimationVariable(int startValue, int endValue, VariableUpdateCallback updateCallback, EasingFunction easingFunction /*= ANIMO_LINEAR_EASING*/):
        startValue(startValue), endValue(endValue), updateCallback(updateCallback), easingFunction(easingFunction) {};

    void update(float time);
};
