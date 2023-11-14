/**
 * Simple fade brightness animation
*/
#pragma once
#include "../lib/Animo/src/animo.h"
#include "anim.h"

class FadeBrightness : Anim {
    private:
        Animation* anim = nullptr;
        unsigned long duration;
        u_int8_t bTarget;
        bool update;

        u_int8_t& brightness;

    public:
        FadeBrightness(u_int8_t& brightness): brightness(brightness) {};

        bool isPlaying() {
            return anim && anim->isActive;
        }

        void setUpdate(bool update) {
            this->update = update;
        }
        void setDuration(unsigned long fadeDuration) {
            this->duration = fadeDuration;
        }
        void setTargetBrightness(u_int8_t bTarget) {
            this->bTarget = bTarget;
        }

        void start() {
            anim = animo.addAnimation(duration);
            anim->addVar(brightness, bTarget,
                [&](const AnimationVariable var) {
                    setBrightness(var.value, update);
                },
                ANIMO_LINEAR_EASING);
            anim->start();          
        }

        void advance() {}
};