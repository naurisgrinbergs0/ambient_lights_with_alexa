#pragma once

#include <Arduino.h>

void linearEasing(AnimationVariable &variable, unsigned long time) {
    variable.value = variable.startValue + (variable.endValue - variable.startValue) * time;
}

void quadraticEasing(AnimationVariable &variable, unsigned long time) {
    float easedT = time * time;
    variable.value = variable.startValue + (variable.endValue - variable.startValue) * easedT;
}

void cubicEasing(AnimationVariable &variable, unsigned long time) {
    float easedT = time * time * (3 - 2 * time);
    variable.value = variable.startValue + (variable.endValue - variable.startValue) * easedT;
}

void sigmoidEasing(AnimationVariable &, unsigned long time) {
    float x = time * 12.0 - 6.0;
    float easedT = 1.0 / (1.0 + exp(-x));
    variable.value = variable.startValue + (variable.endValue - variable.startValue) * easedT;
}

EasingFunction ANIMO_LINEAR_EASING = reinterpret_cast<EasingFunction>(linearEasing);
EasingFunction ANIMO_QUADRATIC_EASING = reinterpret_cast<EasingFunction>(quadraticEasing);
EasingFunction ANIMO_CUBIC_EASING = reinterpret_cast<EasingFunction>(cubicEasing);
EasingFunction ANIMO_SIGMOID_EASING = reinterpret_cast<EasingFunction>(sigmoidEasing);