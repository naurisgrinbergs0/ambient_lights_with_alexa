#include "animCallbacks.h"
#include "animation/animation.h"
#include "animation/animationVariable.h"
#include "animation/easingFunctions.h"
#include "animation/animations/fade.h"

void loopPulseBrigtness() {
    set(255, 0, 0);
    Fade *pulse1 = new Fade(500, 0, 255, 
        reinterpret_cast<AnimationUpdateCallback>(pulseStripBrightnessCallback),
        reinterpret_cast<EasingFunction>(sigmoidEasing));
    Fade *pulse2 = new Fade(500, 255, 0, 
        reinterpret_cast<AnimationUpdateCallback>(pulseStripBrightnessCallback),
        reinterpret_cast<EasingFunction>(sigmoidEasing));
    pulse1->setNext(pulse2);
    pulse2->setNext(pulse1);
    Animator::getInstance()->startLoopAnimation(pulse1);
}

void loopPulsePixelMovement() {
    Fade *pulse1 = new Fade(800, 100, 230, 
        reinterpret_cast<AnimationUpdateCallback>(pulsePixelPositionCallback),
        reinterpret_cast<EasingFunction>(sigmoidEasing));
    Fade *pulse2 = new Fade(800, 230, 100, 
        reinterpret_cast<AnimationUpdateCallback>(pulsePixelPositionCallback),
        reinterpret_cast<EasingFunction>(sigmoidEasing));
    pulse1->setNext(pulse2);
    pulse2->setNext(pulse1);
    Animator::getInstance()->startLoopAnimation(pulse1);
}

void loopColorfulPulse() {
    // Define the pulse for brightness variation
    Fade *brightnessPulse = new Fade(500, 0, 100, 
        reinterpret_cast<AnimationUpdateCallback>(colorfulPulseBrightnessCallback),
        reinterpret_cast<EasingFunction>(sigmoidEasing));
    Fade *brightnessPulse2 = new Fade(500, 100, 0, 
        reinterpret_cast<AnimationUpdateCallback>(colorfulPulseBrightnessCallback),
        reinterpret_cast<EasingFunction>(sigmoidEasing));
    brightnessPulse->setNext(brightnessPulse2);
    brightnessPulse2->setNext(brightnessPulse);

    // Define the pulse for pixel position movement
    Fade *pixelMovementPulse = new Fade(10000, 2, NUM_LEDS - 2, 
        reinterpret_cast<AnimationUpdateCallback>(colorfulPulsePixelMovementCallback),
        reinterpret_cast<EasingFunction>(sigmoidEasing));
    Fade *pixelMovementPulse2 = new Fade(10000, NUM_LEDS - 2, 2, 
        reinterpret_cast<AnimationUpdateCallback>(colorfulPulsePixelMovementCallback),
        reinterpret_cast<EasingFunction>(sigmoidEasing));
    pixelMovementPulse->setNext(pixelMovementPulse2);
    pixelMovementPulse2->setNext(pixelMovementPulse);

    // Start the main animation loop
    Animator::getInstance()->startLoopAnimation(brightnessPulse);
    Animator::getInstance()->startLoopAnimation(pixelMovementPulse);
}

void loopColorSpectrumAnimation() {
    // Define the color spectrum animation
    Fade *colorSpectrumAnimation = new Fade(10000, 0, 65535,
        reinterpret_cast<AnimationUpdateCallback>(colorSpectrumAnimationCallback),
        reinterpret_cast<EasingFunction>(linearEasing));
    colorSpectrumAnimation->setNext(colorSpectrumAnimation);
    
    // Start the color spectrum animation
    Animator::getInstance()->startLoopAnimation(colorSpectrumAnimation);
}

// void loopTwinkleAnimation() {
//   Animation *twinkleAnimation = new Instant(0, NUM_LEDS, reinterpret_cast<AnimationUpdateCallback>(twinkleAnimationCallback));
//     twinkleAnimation->setNext(twinkleAnimation);

//   // Set up the main animation loop
//   Animator::getInstance()->startLoopAnimation(twinkleAnimation);
// }