class Fade : public Animation {
public:
    Fade(long duration, int startValue, int endValue, 
        AnimationUpdateCallback updateCallback, EasingFunction easingFunction) {
        this->updateCallback = updateCallback;
        this->variables[0].easingFunction = easingFunction;
        this->variables[0].duration = duration;
        this->variables[0].startValue = startValue;
        this->variables[0].endValue = endValue;
    }
};