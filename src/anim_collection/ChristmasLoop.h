/**
 * Christmas loop animation
*/
#pragma once
#include "../lib/Animo/src/animo.h"
#include "anim.h"
#include "FadeColor.h"

class ChristmasLoop : public Anim {
    private:
        u_int8_t speed = 100;
        FadeColor* transition;
        Animation* anim;

        RgbColor* colors;

    public:
        ChristmasLoop(RgbColor* colors): colors(colors){};

        void setSpeed(u_int8_t speed) {
            this->speed = speed;
        }

        void start() override {
            // anim = animo.addAnimation(duration, true);
            // anim->addVar(0, 360,
            //     [](const AnimationVariable var) {
            //         setHSV(var.value, 255, 255, true);
            //     },
            //     ANIMO_LINEAR_EASING);

            // transition = new FadeColor(colors);
            // transition->setDuration(400);
            // transition->setTargetRGB(255, 0, 0);
            // transition->onFinished([this]() {
            //     this->anim->start();
            //     delete transition;
            //     transition = nullptr;
            // });
            // transition->start();
            // this->isAnimPlaying = true;
        }

        void onAdvance() {
            if (this->isAnimPlaying) {

            }
        }
};