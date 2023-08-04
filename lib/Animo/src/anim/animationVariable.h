#pragma once

#include <Arduino.h>

struct AnimationVariable;

typedef void (*EasingFunction) (const AnimationVariable *variable, unsigned long time);
typedef void (*VariableUpdateCallback) (const AnimationVariable variable);

struct AnimationVariable {
    int startValue = 0;
    int endValue = 0;
    int value = 0;
    EasingFunction easingFunction = ANIMO_LINEAR_EASING;
    VariableUpdateCallback updateCallback = nullptr;

    AnimationVariable(int startValue, int endValue, VariableUpdateCallback updateCallback, EasingFunction easingFunction)
        startValue(startValue), endValue(endValue), updateCallback(updateCallback), easingFunction(easingFunction);

    void update(unsigned long time);
};
