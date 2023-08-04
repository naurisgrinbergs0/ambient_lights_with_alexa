#pragma once

#include <Arduino.h>
#include "animationVariable.h"
#include "../constants.h"
#include "easingFunctions.h"

class Animation {
private:
    std::vector<AnimationVariable> variables;
    
public:
    bool isLoop = false;
    bool isActive = false;
    unsigned long startTime = 0;
    unsigned long pausedTime = 0;
    unsigned long duration = 0;

    Animation(unsigned long startTime, unsigned long duration, bool isLoop = false):
        startTime(startTime), duration(duration), isLoop(isLoop) {};

    void start();
    void pause();
    void update();

    AnimationVariable* addVar(int startValue, int endValue, VariableUpdateCallback updateCallback, 
        EasingFunction easingFunction = ANIMO_LINEAR_EASING);
    void removeVar(AnimationVariable* variable);
};
