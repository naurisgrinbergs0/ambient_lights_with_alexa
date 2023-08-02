#ifndef animation_h
#define animation_h

#include <Arduino.h>
#include "animationVariable.h"

typedef void (*AnimationUpdateCallback) (const AnimationVariable variables[]);

#define NUM_OF_VARIABLES 5

class Animation {
protected:
    AnimationVariable variables[NUM_OF_VARIABLES];
    
public:
    bool isLoop = false;
    bool isActive = false;
    Animation *nextAnimation = nullptr;
    AnimationUpdateCallback updateCallback;

    void start();
    void update();
    void setNext(Animation *nextAnimation);
};

#endif