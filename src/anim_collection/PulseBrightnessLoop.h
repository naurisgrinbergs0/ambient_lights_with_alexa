/**
 * Pixel rush loop animation
*/
#pragma once
#include "../lib/Animo/src/animo.h"
#include "anim.h"

class PulseBrightnessLoop : Anim {
    private:
        AnimationChain* chain = nullptr;
        unsigned long fadeInDuration;
        unsigned long fadeOutDuration;
        u_int8_t startBrightness;
        u_int8_t endBrightness;

    public:
        bool isPlaying() {
            return chain && chain->isActive;
        }

        void setFadeInDuration(unsigned long fadeInDuration) {
            this->fadeInDuration = fadeInDuration;
        }
        void setFadeOutDuration(unsigned long fadeOutDuration) {
            this->fadeOutDuration = fadeOutDuration;
        }
        void setStartBrightness(u_int8_t startBrightness) {
            this->startBrightness = startBrightness;
        }
        void setEndBrightness(u_int8_t endBrightness) {
            this->endBrightness = endBrightness;
        }

        void start() {
            auto callback = [](const AnimationVariable var) {
                setBrightness(var.value, true);
            };

            chain = animo.addAnimationChain(true);
            Animation* fadeIn = chain->addAnimation(fadeInDuration);
            Animation* fadeOut = chain->addAnimation(fadeOutDuration);
            fadeIn->addVar(startBrightness, endBrightness, callback, ANIMO_SIGMOID_EASING);
            fadeOut->addVar(endBrightness, startBrightness, callback, ANIMO_SIGMOID_EASING);
            chain->start();
        }

        void advance() {}
};