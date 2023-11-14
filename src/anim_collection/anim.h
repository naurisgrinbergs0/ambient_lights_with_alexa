#pragma once

class Anim {
public:
    virtual ~Anim() {}
    
    virtual bool isPlaying() = 0;
    virtual void start() = 0;
    virtual void advance() = 0;
};