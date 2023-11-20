#pragma once

class Anim {
protected:
    std::function<void()> finishedCallback = nullptr;
    bool isAnimPlaying = false;
    
public:
    virtual ~Anim() {}

    bool isPlaying() {
        return this->isAnimPlaying;
    };
    virtual void start() = 0;
    virtual void onAdvance() {}
    void onFinished(std::function<void()> callback) {
        this->finishedCallback = callback;
    }
};