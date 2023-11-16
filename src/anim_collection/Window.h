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
        u_int8_t colorsCurr[NUM_LEDS][3];

    public:
        Window(RgbColor* colors): colors(colors) {};

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
            if (windowMode == WindowMode::NONE) {
                return;
            }

            // set current colors
            for (u_int16_t i = 0; i < NUM_LEDS; i++) {
                this->colorsCurr[i][0] = colors[i].R;
                this->colorsCurr[i][1] = colors[i].G;
                this->colorsCurr[i][2] = colors[i].B;
            }

            u_int16_t halfLength = ceil(NUM_LEDS / 2.0);
            anim = animo.addAnimation(duration);
            anim->addVar(0, halfLength,
                [=](const AnimationVariable var) {
                    setRGB(0, 0, 0); // TODO: simplify the ifs and loops
                    if (windowMode == WindowMode::OPEN) {
                        for (u_int16_t i = 0; i <= var.value; i++) { // Include the most left and right LEDs
                            u_int16_t lowerIndex = max(0, (int)halfLength - i - 1);
                            u_int16_t upperIndex = min(NUM_LEDS - 1, halfLength + i);
                            setRGB(lowerIndex, colorsCurr[lowerIndex][0], colorsCurr[lowerIndex][1], colorsCurr[lowerIndex][2]);
                            setRGB(upperIndex, colorsCurr[upperIndex][0], colorsCurr[upperIndex][1], colorsCurr[upperIndex][2]);
                        }
                    } else { // CLOSE mode
                        for (u_int16_t i = 0; i <= halfLength - var.value; i++) { // Include the middle LED
                            u_int16_t lowerIndex = var.value + i;
                            u_int16_t upperIndex = NUM_LEDS - 1 - i - var.value;
                            setRGB(lowerIndex, colorsCurr[lowerIndex][0], colorsCurr[lowerIndex][1], colorsCurr[lowerIndex][2]);
                            setRGB(upperIndex, colorsCurr[upperIndex][0], colorsCurr[upperIndex][1], colorsCurr[upperIndex][2]);
                        }
                    }
                    show();
                },
                ANIMO_CUBIC_EASING);
            anim->start();          
        }

        void advance() {}
};