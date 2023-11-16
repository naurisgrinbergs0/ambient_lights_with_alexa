#pragma once

#include "../lib/Animo/src/animo.h"

Animo animo = Animo();

// #include "anim_collection/GalacticNebula.h"
#include "anim_collection/FadeBrightness.h"
#include "anim_collection/PulseBrightnessLoop.h"
#include "anim_collection/RainbowLoop.h"
#include "anim_collection/PixelRushLoop.h"
#include "anim_collection/FadeColor.h"
#include "anim_collection/Window.h"

RgbColor WHITE_LIGHT = RgbColor(255, 255, 255);
RgbColor DANGER_LIGHT = RgbColor(255, 0, 0);

// GalacticNebula* galacticNebula;
RainbowLoop* rainbowLoop;
PixelRushLoop* pixelRushLoop;
PulseBrightnessLoop* pulseBrightnessLoop;
FadeColor* fadeColor;
FadeBrightness* fadeBrightness;

Window* bootAnim;

void initHandlers() {
    // galacticNebula = new GalacticNebula();
    rainbowLoop = new RainbowLoop(stripState.colors);
    pixelRushLoop = new PixelRushLoop();
    pulseBrightnessLoop = new PulseBrightnessLoop();
    fadeColor = new FadeColor(stripState.colors);
    fadeBrightness = new FadeBrightness(stripState.brightness);
    bootAnim = new Window(stripState.colors);
}

void stopAllAnims() {
    animo.removeAllAnimations(false);
    animo.removeAllAnimationChains(false);
}

void advanceAllAnims() {
    if (pixelRushLoop->isPlaying()) {
        pixelRushLoop->advance();
    }
    if (rainbowLoop->isPlaying()) {
        rainbowLoop->advance();
    }
    if (stripState.isTurningOff && !bootAnim->isPlaying()) {
        stripState.isTurningOff = false;
        stripState.isOn = false;
        stopAllAnims();
    }
}

// =======================================

void handleLightsOn()  {
    if (!stripState.isOn) {
        setBrightness(255);
        bootAnim->setModeOpen();
        bootAnim->setDuration(200);
        bootAnim->start();
        stripState.isTurningOn = true;
        stripState.isOn = true;
    }
}
void handleLightsOff()  {
    if (stripState.isOn) { 
        stripState.isTurningOff = true;
        bootAnim->setModeClose();
        bootAnim->setDuration(200);
        bootAnim->start();
    }
}

void handleLightToggle()  {
    if (!stripState.isOn) {
        setRGB(WHITE_LIGHT.R, WHITE_LIGHT.G, WHITE_LIGHT.B);
        handleLightsOn();
    } else {
        handleLightsOff();
    }
}

void handleNightLight() {
    if (stripState.isOn) {
        stopAllAnims();
    } else {
        stripState.isOn = true;
    }

    u_int16_t startPixel = 110;

    fadeBrightness->setTargetBrightness(255);
    fadeBrightness->setDuration(500);
    fadeBrightness->setUpdate(false);
    fadeBrightness->start();


    for (u_int16_t i = 0; i < NUM_LEDS; i++) {
        if (i < startPixel) {
            fadeColor->setTargetRGB(i, 0, 0, 0);
        } else {
            fadeColor->setTargetRGB(i, WHITE_LIGHT.R, WHITE_LIGHT.G, WHITE_LIGHT.B);
        }
    }
    fadeColor->setDuration(500);
    fadeColor->start();
}

void handleRainbow()  {
    if (!stripState.isOn) {
        handleLightsOn();
    } else {
        if (!rainbowLoop->isPlaying()) {
            stopAllAnims();
        }
    }
    if (!rainbowLoop->isPlaying()) {
        rainbowLoop->setDuration(10000);
        rainbowLoop->start();
    }
}

void handlePixelRush() {
    if (!stripState.isOn) {
        handleLightsOn();
    } else {
        if (!pixelRushLoop->isPlaying()) {
            stopAllAnims();
        }
    }
    if (!pixelRushLoop->isPlaying()) {
        pixelRushLoop->start();
    }
}

void handleDanger() {
    if (stripState.isOn) {
        if (!pulseBrightnessLoop->isPlaying()) {
            stopAllAnims();
        }
    }
    if (!pulseBrightnessLoop->isPlaying()) {
        setRGB(DANGER_LIGHT.R, DANGER_LIGHT.G, DANGER_LIGHT.B);
        pulseBrightnessLoop->setFadeInDuration(1000);
        pulseBrightnessLoop->setFadeOutDuration(500);
        pulseBrightnessLoop->setStartBrightness(0);
        pulseBrightnessLoop->setEndBrightness(255);
        pulseBrightnessLoop->start();
        stripState.isOn = true;
    }
}

void handleNetflixAndChill()  {
    if (!stripState.isOn) {
        handleLightsOn();
    } else {
        if (!fadeColor->isPlaying()) {
            stopAllAnims();
        }
    }
    if (!fadeColor->isPlaying()) {
        fadeBrightness->setTargetBrightness(80);
        fadeBrightness->setDuration(500);
        fadeBrightness->setUpdate(false);
        fadeBrightness->start();
        
        fadeColor->setDuration(1000);
        fadeColor->setTargetRGB(255, 33, 140);
        fadeColor->start();
    }
}