/**
 * Christmas loop animation - Chase mode
*/
#pragma once
#include <Arduino.h>
#include "ChristmasLoop.h"

class ModeChase { 
    private:
        std::vector<RgbColor> christmasColors = {
            RgbColor(255, 0, 0),
            RgbColor(0, 255, 0),
            RgbColor(255, 221, 0),
            RgbColor(0, 0, 255)
        };
        unsigned long lastRandomizeParamsTime;
        unsigned long lastAdvanceTime;
        u_int16_t index = 0;
        
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
        u_int16_t groupSize;
        u_int16_t stepSize;
        u_int16_t gapSize;
        bool moveForward;

        ModeChase() {
            randomizeParamsRate = random(5000, 10000);
            updateRate = random(100, 1500);
        };

        void randomizeParams() {
            randomizeParamsRate = random(5000, 10000);
            updateRate = random(100, 1200);
            groupSize = random(2, 10);
            stepSize = random(2, 10);
            gapSize = random(10 - groupSize, 20);
            moveForward = random(0, 2);
        }

        void advance() {
            if (isReadyToAdvance()) {
                if (isReadyToRandomizeParams()) {
                    randomizeParams();
                }

                u_int8_t colorListSize = christmasColors.size();
                u_int16_t totalGroupSize = groupSize + gapSize;
                for (u_int16_t i = 0; i < NUM_LEDS; i++) {
                    // calculate which group this LED belongs to
                    u_int16_t adjustedIndex = moveForward ? (i + index) : (NUM_LEDS - 1 - i + index);
                    u_int16_t groupIndexWithGap = (adjustedIndex / totalGroupSize) % colorListSize;
                    bool isInGap = (adjustedIndex % totalGroupSize) >= groupSize;
                    
                    if (isInGap) {
                        setRGB(i, 0, 0, 0);
                    } else {
                        setRGB(i, 
                            christmasColors[groupIndexWithGap].R, 
                            christmasColors[groupIndexWithGap].G, 
                            christmasColors[groupIndexWithGap].B
                        );
                    }
                }
                show();

                // increment the index by step size
                index = (index + stepSize) % (NUM_LEDS * totalGroupSize / colorListSize);
            }
        }
    };