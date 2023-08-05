#pragma once

#include <Arduino.h>
#include "animationVariable.h"

void linearEasing(AnimationVariable &variable, float time);
void quadraticEasing(AnimationVariable &variable, float time);
void cubicEasing(AnimationVariable &variable, float time);
void sigmoidEasing(AnimationVariable &variable, float time);
void fastSigmoidEasing(AnimationVariable &variable, float time);