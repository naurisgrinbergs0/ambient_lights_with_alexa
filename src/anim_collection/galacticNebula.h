#pragma once
#include "../lib/Animo/src/animo.h"
#include "anim.h"

class NebulaCloud;
// static void cloudUpdateCallback(const AnimationVariable var, u_int16_t cloudSize);

class GalacticNebula : Anim {
private:
    class NebulaCloud { 
    public:
        u_int16_t cloudSize, centerHue;
        int16_t startPos, endPos;
        float gradStep;

// TODO: current problem - when [cloudSize] passed in labda function capture list the value of it changes
// this prbbly happens because the object is destroyed so random value is ..
        NebulaCloud() {
            cloudSize = random(20, NUM_LEDS / 4);
            u_int16_t halfCloud = cloudSize / 2;
            int16_t minPos = -halfCloud;
            int16_t maxPos = NUM_LEDS + halfCloud;
            startPos = random(minPos, maxPos);
            endPos = startPos < 0 || startPos - cloudSize < 0
                ? random(startPos + cloudSize, maxPos)
                : random(startPos - cloudSize, minPos);
            // unsigned long duration = random(5000, 10000);
            centerHue = random(0, 360);
            gradStep = (float)random(10, 20) / 10.0f;

            // Animation* cloudPosAnim = animo.addAnimation(duration);
            // cloudPosAnim->addVar(startPos, endPos, [cloudSize](const AnimationVariable var) -> void {
            //     cloudUpdateCallback(var, cloudSize);
            // }, ANIMO_LINEAR_EASING);
            // cloudPosAnim->start();
        };
    };

    static void cloudUpdateCallback(const AnimationVariable var, u_int16_t cloudSize) {
            Serial.println(cloudSize);
            // Serial.printf(" %d %d %d %d\n", cloudSize, centerHue, startPos, endPos);
            // clear();
            // u_int16_t halfCloud = cloudSize / 2;
            // float gradVal = centerHue - (halfCloud * gradStep);
            
            // // Loop through the LEDs within the cloud range
            // for (int16_t i = var.value - halfCloud; i <= var.value + halfCloud; i++) {
            //     if (i < 0 || i > NUM_LEDS - 1) {
            //         continue;
            //     }
            //     RgbColor backgroundColor = get(i);
            
            //     RgbColor cloudColor = HSVtoRGB((u_int16_t)gradVal, 255, 255);

            //     // Calculate the blending factor based on the distance from the cloud center
            //     float distanceFromCenter = abs(i - var.value);
            //     float blendingFactor = 1.0 - (distanceFromCenter / halfCloud);

            //     // Blend the cloud color and background color using the blending factor
            //     u_int8_t r = (uint8_t)(cloudColor.R * blendingFactor + backgroundColor.R * (1 - blendingFactor));
            //     u_int8_t g = (uint8_t)(cloudColor.G * blendingFactor + backgroundColor.G * (1 - blendingFactor));
            //     u_int8_t b = (uint8_t)(cloudColor.B * blendingFactor + backgroundColor.B * (1 - blendingFactor));

            //     // Serial.printf("\nr: %s g: %s b: %s", r, g, b);

            //     setRGB(i, r, g, b);
            //     gradVal += gradStep;
            // }
            // show();
        }

    std::vector<NebulaCloud> clouds;
    unsigned long latestCloudSpawnTime;

public:
    void start() {
        latestCloudSpawnTime = millis();
        clouds.push_back(NebulaCloud());
    }

    void advance() {
        // if (clouds.size() < 2 && millis() - latestCloudSpawnTime > 20000) {
        //     latestCloudSpawnTime = millis();
        //     clouds.push_back(NebulaCloud());
        // }
    }
};