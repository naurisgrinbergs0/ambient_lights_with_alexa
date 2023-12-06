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
        unsigned long lastAdvanceTime;
        u_int8_t currentBrightness;
        
        bool isReadyToAdvance() {
            if (millis() - lastAdvanceTime >= updateRate) {
                lastAdvanceTime = millis();
                return true;
            }
            return false;
        }
        bool isReadyToRandomizeParams() {
            if (millis() - lastRandomizeParamsTime >= randomizeParamsRate) {
                lastRandomizeParamsTime = millis();
                return true;
            }
            return false;
        }

    public:
        unsigned long randomizeParamsRate;
        unsigned long updateRate;
        unsigned long holdTime;
        u_int16_t offset;
        u_int16_t groupSize;
        u_int16_t gapSize;
        u_int8_t targetBrightness;
        int8_t fadeStep = 2;
        u_int8_t currentColorIndex;

        ModeBlink() {
            randomizeParamsRate = random(5000, 10000);
            updateRate = random(0, 30);
        };

        void randomizeParams() {
            randomizeParamsRate = random(5000, 10000);
            targetBrightness = random(50, 255);
            updateRate = random(0, 30);
            holdTime = random(100, 1000);
            groupSize = random(1, 6);
            gapSize = random(10 - groupSize, 30);
            offset = random(0, gapSize);
            currentColorIndex = random(0, 4);
        }

        void advance() {
            unsigned long currentMillis = millis();

            if (currentMillis - lastAdvanceTime >= updateRate) {
                lastAdvanceTime = currentMillis;

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
                setBrightness(???);
                show();
            }

            if (currentMillis - lastAdvanceTime >= holdTime) {
                lastAdvanceTime = currentMillis;
            }
        }
    };

    ////// TODO: MBY USE MY ANIMATION LIB?