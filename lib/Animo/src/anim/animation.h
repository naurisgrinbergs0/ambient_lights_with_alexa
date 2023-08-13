#pragma once

#include <Arduino.h>
#include "animationVariable.h"

typedef void (*VariableUpdateCallback) (const AnimationVariable variable);
typedef void (*EasingFunction) (const AnimationVariable *variable, float time);

class Animation {
private:
    std::vector<AnimationVariable> variables;
    
public:
    unsigned long startTime = 0;
    unsigned long pausedTime = 0;
    unsigned long duration = 0;
    bool isLoop = false;
    bool isActive = false;

    Animation(unsigned long duration, bool isLoop = false):
        duration(duration), isLoop(isLoop) {};

    void start();
    void pause();
    void update();

    AnimationVariable addVar(int startValue, int endValue, VariableUpdateCallback updateCallback, 
        EasingFunction easingFunction /*= ANIMO_LINEAR_EASING*/);
    void removeVar(AnimationVariable* variable);
};
