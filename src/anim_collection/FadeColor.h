/**
 * Simple color fade
*/
#pragma once
#include "../lib/Animo/src/animo.h"
#include "anim.h"

class FadeColor : Anim {
    private:
        enum class ColorMode {
            RGB,
            NONE,
        };

        u_int8_t UPDATE_THRESHOLD = 2; // ensures that minor changes don't trigger strip update

        RgbColor* colors;

        Animation* anim = nullptr;
        unsigned long fadeDuration;
        float values[NUM_LEDS][3];
        // rgb
        u_int8_t rgbStart[NUM_LEDS][3];
        u_int8_t rgbTarget[NUM_LEDS][3];
        ColorMode colorMode = ColorMode::NONE;

    public:
        FadeColor(RgbColor* colors): colors(colors){};

        bool isPlaying() {
            return anim && anim->isActive;
        }

        void setDuration(unsigned long fadeDuration) {
            this->fadeDuration = fadeDuration;
        }

        void setTargetRGB(u_int8_t rTarget, u_int8_t gTarget, u_int8_t bTarget) {
            colorMode = ColorMode::RGB;
            for (u_int16_t i = 0; i < NUM_LEDS; i++) {
                this->rgbTarget[i][0] = rTarget;
                this->rgbTarget[i][1] = gTarget;
                this->rgbTarget[i][2] = bTarget;
            }
        }
        void setTargetRGB(u_int16_t pixel, u_int8_t rTarget, u_int8_t gTarget, u_int8_t bTarget) {
            colorMode = ColorMode::RGB;
            this->rgbTarget[pixel][0] = rTarget;
            this->rgbTarget[pixel][1] = gTarget;
            this->rgbTarget[pixel][2] = bTarget;
        }

        void start() {
            if (colorMode == ColorMode::NONE) {
                return;
            }

            // calculate delta for each subpixel & set start values
            if (colorMode == ColorMode::RGB) {
                for (u_int16_t i = 0; i < NUM_LEDS; i++) {
                    rgbStart[i][0] = colors[i].R;
                    rgbStart[i][1] = colors[i].G;
                    rgbStart[i][2] = colors[i].B;
                    values[i][0] = (rgbTarget[i][0] - colors[i].R) / 255.0;
                    values[i][1] = (rgbTarget[i][1] - colors[i].G) / 255.0;
                    values[i][2] = (rgbTarget[i][2] - colors[i].B) / 255.0;
                }
            }

            anim = animo.addAnimation(fadeDuration);
            if (colorMode == ColorMode::RGB) {
                anim->addVar(0, 255, [&](const AnimationVariable var) {
                    boolean update = false;
                    for (u_int16_t i = 0; i < NUM_LEDS; i++) {
                        u_int8_t r = (u_int8_t)(rgbStart[i][0] + var.value * values[i][0]);
                        u_int8_t g = (u_int8_t)(rgbStart[i][1] + var.value * values[i][1]);
                        u_int8_t b = (u_int8_t)(rgbStart[i][2] + var.value * values[i][2]);
                        if (abs(r - colors[i].R) > UPDATE_THRESHOLD 
                            || abs(g - colors[i].G) > UPDATE_THRESHOLD 
                            || abs(b - colors[i].B) > UPDATE_THRESHOLD) {
                            setRGB(i, r, g, b);
                            update = true;
                        }
                    }
                    if (update) {
                        show();
                    }
                }, ANIMO_SIGMOID_EASING);
            }
            anim->start();
        }

        void advance() {}
};