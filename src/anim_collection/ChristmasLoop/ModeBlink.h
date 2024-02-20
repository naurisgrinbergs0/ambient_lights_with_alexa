/**
 * Christmas loop animation - Blink mode
*/
#pragma once
#include <Arduino.h>
#include "ChristmasLoop.h"

class ModeBlink { 
    private:
        std::vector<RgbColor> christmasColors = {
            RgbColor(255, 0, 0),
            RgbColor(0, 255, 0),
            RgbColor(255, 221, 0),
            RgbColor(0, 0, 255)
        };
        unsigned long lastRandomizeParamsTime;
        Animation* anim = nullptr;
        bool fadeIn = true;
        
        bool isReadyToRandomizeParams() {
            if (!fadeIn && millis() - lastRandomizeParamsTime >= randomizeParamsRate) {
                lastRandomizeParamsTime = millis();
                return true;
            }
            return false;
        }

    public:
        unsigned long randomizeParamsRate;
        unsigned long fadeTime;
        u_int16_t offset;
        u_int16_t groupSize;
        u_int16_t gapSize;
        u_int8_t targetBrightness;
        u_int8_t currentColorIndex;

        ModeBlink() {
            randomizeParams();
            startAnim();
        };

        void randomizeParams() {
            randomizeParamsRate = random(5000, 10000);
            targetBrightness = random(50, 255);
            fadeTime = random(1000, 5000);
            groupSize = random(1, 6);
            gapSize = random(10 - groupSize, 30);
            offset = random(0, gapSize);
            currentColorIndex = random(0, 4);
        }

        void startAnim() {
            anim = animo.addAnimation(fadeTime, true);
            anim->setIterationFinishedCallback([this]() {
                updateAll();
                fadeIn = !fadeIn;
            });
            anim->addVar(0, targetBrightness, [&](const AnimationVariable var) {
                // Serial.printf("\n%d %d %d", targetBrightness, var.value, fadeIn ? var.value : targetBrightness - var.value);
                setBrightness(fadeIn ? var.value : targetBrightness - var.value, true);
            }, ANIMO_CUBIC_EASING);
            anim->start();
        }

        void updateAll() {
            if (isReadyToRandomizeParams()) {
                randomizeParams();

                for (u_int16_t i = 0; i < NUM_LEDS; i++) {
                    u_int16_t groupPosition = (i + offset) % (groupSize + gapSize);

                    if (groupPosition < groupSize) {
                        setRGB(i,
                            christmasColors[currentColorIndex].R, 
                            christmasColors[currentColorIndex].G, 
                            christmasColors[currentColorIndex].B
                        );
                    } else {
                        setRGB(i, 0, 0, 0);
                    }
                }
            }
        }
    };