#include <Arduino.h>
#include "animation/animationVariable.h"

void linearEasing(AnimationVariable &variable) {
    float t = float(millis() - variable.startTime) / variable.duration;
    variable.value = variable.startValue + (variable.endValue - variable.startValue) * t;
}

void quadraticEasing(AnimationVariable &variable) {
    float t = float(millis() - variable.startTime) / variable.duration;
    t = constrain(t, 0.0, 1.0);
    float easedT = t * t;
    variable.value = variable.startValue + (variable.endValue - variable.startValue) * easedT;
}

void cubicEasing(AnimationVariable &variable) {
    float t = float(millis() - variable.startTime) / variable.duration;
    t = constrain(t, 0.0, 1.0);
    float easedT = t * t * (3 - 2 * t);
    variable.value = variable.startValue + (variable.endValue - variable.startValue) * easedT;
}

void sigmoidEasing(AnimationVariable &variable) {
    float t = float(millis() - variable.startTime) / variable.duration;
    t = constrain(t, 0.0, 1.0);

    float x = t * 12.0 - 6.0;
    float easedT = 1.0 / (1.0 + exp(-x));

    variable.value = variable.startValue + (variable.endValue - variable.startValue) * easedT;
}