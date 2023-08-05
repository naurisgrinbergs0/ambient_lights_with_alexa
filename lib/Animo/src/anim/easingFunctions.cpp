#include "easingFunctions.h"

void linearEasing(AnimationVariable &variable, float time) {
    variable.value = variable.startValue + (variable.endValue - variable.startValue) * time;
}

void quadraticEasing(AnimationVariable &variable, float time) {
    float easedT = time * time;
    variable.value = variable.startValue + (variable.endValue - variable.startValue) * easedT;
}

void cubicEasing(AnimationVariable &variable, float time) {
    float easedT = time * time * (3 - 2 * time);
    variable.value = variable.startValue + (variable.endValue - variable.startValue) * easedT;
}

void sigmoidEasing(AnimationVariable &variable, float time) {
    float x = time * 12.0 - 6.0;
    float easedT = 1.0 / (1.0 + exp(-x));
    variable.value = variable.startValue + (variable.endValue - variable.startValue) * easedT;
}

void fastSigmoidEasing(AnimationVariable &variable, float time) {
    float x = time * 12.0 - 6.0;
    float halfX = x * 0.5;
    int i;
    memcpy(&i, &x, sizeof(int));
    i = 0x5F3759DF - (i >> 1);
    memcpy(&x, &i, sizeof(float));
    x = x * (1.5 - halfX * x * x);
    float easedT = 0.5 + 0.5 * x;
    variable.value = variable.startValue + (variable.endValue - variable.startValue) * easedT;
}