#ifndef animator_h
#define animator_h

#include "animation/animation.h"

#define NUM_OF_ANIMATIONS 5

class Animator {
private:
    static Animator* instance;
    
    Animation* animations[NUM_OF_ANIMATIONS] = { nullptr };

public:
    static Animator* getInstance();

    void advanceAnimations();
    void startAnimation(Animation *animation);
    void startLoopAnimation(Animation *animation);
    bool getIsActive();
};

#endif