#pragma once

#include "../lib/Animo/src/animo.h"

Animo animo = Animo();

/**
 * Fades strip brightness in & out indefinitely
*/
void loopFadeBrightness() {
    auto callback = [](const AnimationVariable var) {
        setBrightness(var.value);
        show();
    };

    AnimationChain* fadeChain = animo.addAnimationChain(true);
    Animation* fadeIn = fadeChain->addAnimation(1000);
    Animation* fadeOut = fadeChain->addAnimation(1000);
    fadeIn->addVar(0, 255, callback, ANIMO_SIGMOID_EASING);
    fadeOut->addVar(255, 0, callback, ANIMO_SIGMOID_EASING);
    fadeChain->start();
}

/**
 * Simple fade-in animation
*/
void fadeInBrightness() {
    Animation* fadeIn = animo.addAnimation(500);
    fadeIn->addVar(0, 255, 
        [](const AnimationVariable var) {
            setBrightness(var.value);
            show();
        },
        ANIMO_SIGMOID_EASING);
    fadeIn->start();
}

/**
 * Simple fade-out animation
*/
void fadeOutBrightness() {
    Animation* fadeOut = animo.addAnimation(500);
    fadeOut->addVar(255, 0,
        [](const AnimationVariable var) {
            setBrightness(var.value);
            show();
        },
        ANIMO_SIGMOID_EASING);
    fadeOut->start();
}