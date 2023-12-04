/**
 * Pixel rush loop animation
*/
#pragma once
#include "../lib/Animo/src/animo.h"
#include "anim.h"

class PixelRushLoop : public Anim {
    private:
        Animation* anim = nullptr;
        u_int16_t startValue = 0;
        bool forward = true;

        void createAnimAndStart() {
            u_int16_t endValue = forward ? random(NUM_LEDS / 2, NUM_LEDS) : random(0, NUM_LEDS / 2);
            unsigned long duration = ((float)abs(startValue - endValue) / (float)NUM_LEDS) * 500.0;
            anim = animo.addAnimation(duration);
            anim->addVar(startValue, endValue, 
                [](const AnimationVariable var) {
                    clear();
                    setRGB(var.value, 255, 255, 255, true);
                },
                ANIMO_CUBIC_EASING);
            anim->start();
            this->isAnimPlaying = true;
            startValue = endValue;
        }

    public:
        void start() override {
            createAnimAndStart();
        }

        void onAdvance() {
            if (this->isAnimPlaying) {
                if (anim && !anim->isActive) {
                    createAnimAndStart();
                }
            }
        }
};