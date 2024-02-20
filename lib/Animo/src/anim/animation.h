#pragma once

#include <Arduino.h>
#include "animationVariable.h"

typedef void (*EasingFunction) (const AnimationVariable *variable, float time);

class Animation {
private:
    std::vector<AnimationVariable> variables;
    
public:
    String name = "";
    unsigned long startTime = 0;
    unsigned long pausedTime = 0;
    unsigned long duration = 0;
    bool isLoop = false;
    bool isActive = false;
    bool isFinished = false;
    std::function<void()> finishedCallback = nullptr;
    std::function<void()> iterationFinishedCallback = nullptr;

    Animation(unsigned long duration, bool isLoop = false): duration(duration), isLoop(isLoop) {};

    void start();
    void pause();
    void update();

    void addVar(int startValue, int endValue, std::function<void(const AnimationVariable)> updateCallback, 
        EasingFunction easingFunction);
    void setFinishedCallback(std::function<void()> finishedCallback);
    void setIterationFinishedCallback(std::function<void()> iterationFinishedCallback);
    void removeVar(AnimationVariable* variable);
};
