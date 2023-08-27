#pragma once

class Anim {
public:
    virtual ~Anim() {}
    
    virtual void start() = 0;
    virtual void advance() = 0;
};