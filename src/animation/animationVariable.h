#ifndef animationVariable_h
#define animationVariable_h

struct AnimationVariable;

typedef void (*EasingFunction) (const AnimationVariable *variable);

struct AnimationVariable {
    int startValue = 0;
    int endValue = 0;
    unsigned long startTime = 0;
    unsigned long duration = 0;
    int value = 0;
    EasingFunction easingFunction = nullptr;

    void reset();
    void update();
};

#endif