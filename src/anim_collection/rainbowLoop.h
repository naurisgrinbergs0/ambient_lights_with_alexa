/**
 * Rainbow loop animation
*/
#pragma once
#include "../lib/Animo/src/animo.h"
#include "anim.h"
#include "FadeColor.h"

class RainbowLoop : public Anim {
    private:
        unsigned long duration;
        FadeColor* transition;
        Animation* anim;

        RgbColor* colors;

    public:
        RainbowLoop(RgbColor* colors): colors(colors){};

        void setDuration(unsigned long duration) {
            this->duration = duration;
        }

        void start() override {
            anim = animo.addAnimation(duration, true);
            anim->addVar(0, 360,
                [](const AnimationVariable var) {
                    setHSV(var.value, 255, 255, true);
                },
                ANIMO_LINEAR_EASING);

            transition = new FadeColor(colors);
            transition->setDuration(400);
            transition->setTargetRGB(255, 0, 0);
            transition->onFinished([this]() {
                this->anim->start();
                delete transition;
                transition = nullptr;
            });
            transition->start();
            this->isAnimPlaying = true;

            // TODO: should set anim as not playing when it ends (its a loop - so when loop is stopped)
        }
};