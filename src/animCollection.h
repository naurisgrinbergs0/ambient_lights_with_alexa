#pragma once

#include "anim/fade.h"
#include "../lib/Animo/src/animo.h"
#include "../lib/Animo/src/anim/easingFunctions.h"

Animo animo = Animo();

/**
 * Fades strip brightness in & out indefinitely
*/
void loopFadeBrightness() {
    auto callback = [](const AnimationVariable variables[]) {
        setBrightness(variables[0].value);
        show();
    };

    set(255, 0, 0);
    Fade *fade1 = new Fade(500, 0, 255, callback, ANIMO_SIGMOID_EASING);
    Fade *fade2 = new Fade(500, 255, 0, callback, ANIMO_SIGMOID_EASING);
    fade1->setNext(fade2);
    fade2->setNext(fade1);
    animo.startLoopAnimation(fade1);
}

void loopFadePixelMovement() {
    auto callback = [](const AnimationVariable variables[]) {
        set(0, 0, 0);
        set(variables[0].value-1, 255, 255, 0);
        set(variables[0].value, 0, 255, 255);
        set(variables[0].value+1, 255, 0, 255);
        show();
    };

    Fade *fade1 = new Fade(800, 100, 230, callback, ANIMO_SIGMOID_EASING);
    Fade *fade2 = new Fade(800, 230, 100, callback, ANIMO_SIGMOID_EASING);
    fade1->setNext(fade2);
    fade2->setNext(fade1);
    animo.startLoopAnimation(fade1);
}

void loopColorfulFade() {
    auto callbackBrightness = [](const AnimationVariable variables[]) {
        setBrightness(variables[0].value);
        show();
    };
    auto callbackPosition = [](const AnimationVariable variables[]) {
        int position = variables[0].value;
        set(0, 0, 0);
        set(position - 1, 255, 255, 0);
        set(position, 0, 255, 255);
        set(position + 1, 255, 0, 255);
        show();
    };

    // Define the fade for brightness variation
    Fade *brightnessFade = new Fade(500, 0, 100, callbackBrightness, ANIMO_SIGMOID_EASING);
    Fade *brightnessFade2 = new Fade(500, 100, 0, callbackBrightness, ANIMO_SIGMOID_EASING);
    brightnessFade->setNext(brightnessFade2);
    brightnessFade2->setNext(brightnessFade);

    // Define the fade for pixel position movement
    Fade *pixelMovementFade = new Fade(10000, 2, NUM_LEDS - 2, callbackPosition, ANIMO_SIGMOID_EASING);
    Fade *pixelMovementFade2 = new Fade(10000, NUM_LEDS - 2, 2, callbackPosition, ANIMO_SIGMOID_EASING);
    pixelMovementFade->setNext(pixelMovementFade2);
    pixelMovementFade2->setNext(pixelMovementFade);

    // Start the main animation loop
    animo.startLoopAnimation(brightnessFade);
    animo.startLoopAnimation(pixelMovementFade);
}

void loopColorSpectrumAnimation() {
    auto callback = [](const AnimationVariable variables[]) {
        float t = float(millis() - variables[0].startTime) / variables[0].duration;
        t = constrain(t, 0.0, 1.0);
        int hueValue = int(t * 65535.0);
        for (int i = 0; i < 20; i++) {
            setHSV(i, hueValue, 255, 255);
        }
        show();
    };

    // Define the color spectrum animation
    Fade *colorSpectrumAnimation = new Fade(10000, 0, 65535, callback, ANIMO_LINEAR_EASING);
    colorSpectrumAnimation->setNext(colorSpectrumAnimation);
    
    // Start the color spectrum animation
    animo.startLoopAnimation(colorSpectrumAnimation);
}

/**
 * Simple fade-in animation
*/
void fadeIn(u_int8_t red, u_int8_t green, u_int8_t blue) {
    set(red, green, blue);
    Fade *fadeIn = new Fade(500, 0, 255, 
        [](const AnimationVariable variables[]) {
            setBrightness(variables[0].value);
            show();
        },
        ANIMO_SIGMOID_EASING);
    animo.startAnimation(fadeIn);
}

/**
 * Simple fade-out animation
*/
void fadeOut() {
    Fade *fadeOut = new Fade(500, 0, 255, 
        [](const AnimationVariable variables[]) {
            setBrightness(variables[0].value);
            show();
        },
    ANIMO_SIGMOID_EASING);
    animo.startAnimation(fadeOut);
}