/**
 * Simple fade brightness animation
*/
#pragma once
#include "../lib/Animo/src/animo.h"
#include "anim.h"

class FadeBrightness : public Anim {
    private:
        Animation* anim = nullptr;
        unsigned long duration;
        u_int8_t bTarget;
        bool update;

        u_int8_t& brightness;

    public:
        FadeBrightness(u_int8_t& brightness): brightness(brightness) {};

        void setUpdate(bool update) {
            this->update = update;
        }
        void setDuration(unsigned long fadeDuration) {
            this->duration = fadeDuration;
        }
        void setTargetBrightness(u_int8_t bTarget) {
            this->bTarget = bTarget;
        }

        void start() override {
            anim = animo.addAnimation(duration);
            anim->addVar(brightness, bTarget,
                [&](const AnimationVariable var) {
                    setBrightness(var.value, update);
                },
                ANIMO_LINEAR_EASING);
            anim->setFinishedCallback([this]() {
                this->isAnimPlaying = false;
                if (this->finishedCallback) {
                    this->finishedCallback();
                }
            });
            anim->start();
            this->isAnimPlaying = true;
        }
};