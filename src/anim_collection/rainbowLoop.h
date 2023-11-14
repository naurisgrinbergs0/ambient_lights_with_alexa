/**
 * Rainbow loop animation
*/
#pragma once
#include "../lib/Animo/src/animo.h"
#include "anim.h"
#include "FadeColor.h"

class RainbowLoop : Anim {
    private:
        unsigned long duration;
        FadeColor* transition;
        Animation* anim;

        RgbColor* colors;

        void startRainbowAnim() {
            anim->start();
        }

    public:
        RainbowLoop(RgbColor* colors): colors(colors){};

        bool isPlaying() {
            return (anim && anim->isActive) || (transition && transition->isPlaying());
        }

        void setDuration(unsigned long duration) {
            this->duration = duration;
        }

        void start() {
            anim = animo.addAnimation(duration, true);
            anim->addVar(0, 360,
                [](const AnimationVariable var) {
                    setHSV(var.value, 255, 255, true);
                },
                ANIMO_LINEAR_EASING);
            transition = new FadeColor(colors);
            transition->setDuration(400);
            transition->setTargetRGB(255, 0, 0);
            transition->start();
        }

        void advance() {
            if (transition && !transition->isPlaying() && anim && !anim->isActive) {
                delete transition;
                transition = nullptr;
                startRainbowAnim();
            }
        }
};