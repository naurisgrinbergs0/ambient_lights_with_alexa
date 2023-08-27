/**
 * Rainbow loop animation
*/
#pragma once
#include "../lib/Animo/src/animo.h"
#include "anim.h"

class RainbowLoop : Anim {
    private:
        unsigned long duration;
        Animation* rainbow;

    public:
        RainbowLoop(unsigned long duration): duration(duration) {}

        ~RainbowLoop() {}

        void start() {
            rainbow = animo.addAnimation(duration, true);
            rainbow->addVar(0, 360,
                [](const AnimationVariable var) {
                    setHSV(var.value, 255, 255, true);
                },
                ANIMO_LINEAR_EASING);
            rainbow->start();
        }

        void advance() {}
};