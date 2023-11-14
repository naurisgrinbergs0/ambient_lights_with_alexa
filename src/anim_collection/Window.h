/**
 * Boot animation
*/
#pragma once
#include "../lib/Animo/src/animo.h"
#include "anim.h"

class Window : Anim {
    private:
        enum class WindowMode {
            OPEN,
            CLOSE,
            NONE,
        };

        Animation* anim = nullptr;
        unsigned long duration;
        WindowMode windowMode = WindowMode::NONE;

        RgbColor* colors;

    public:
        Window(RgbColor* colors): colors(colors){};

        bool isPlaying() {
            return anim && anim->isActive;
        }

        void setDuration(unsigned long fadeDuration) {
            this->duration = fadeDuration;
        }
        void setModeOpen() {
            this->windowMode = WindowMode::OPEN;
        }
        void setModeClose() {
            this->windowMode = WindowMode::CLOSE;
        }
        

        void start() {
            u_int16_t halfLength = ceil(NUM_LEDS / 2.0);

            anim = animo.addAnimation(duration);
            anim->addVar(0, halfLength,
                [=](const AnimationVariable var) {
                    for (u_int16_t i = 0; i < var.value; i++) { // TODO: no need to loop through the pixels that are already ON
                        u_int16_t lowerIndex = halfLength - i;
                        u_int16_t upperIndex = halfLength + i;
                        setRGB(lowerIndex, colors[lowerIndex].R, colors[lowerIndex].G, colors[lowerIndex].B);
                        setRGB(upperIndex, colors[upperIndex].R, colors[upperIndex].G, colors[upperIndex].B);
                    }
                },
                ANIMO_LINEAR_EASING);
            anim->start();          
        }

        void advance() {}
};