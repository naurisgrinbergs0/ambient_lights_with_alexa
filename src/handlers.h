#pragma once

#include "../lib/Animo/src/animo.h"

Animo animo = Animo();

#include "anim_collection/fadeBrightness.h"
#include "anim_collection/loopFadeBrightness.h"
#include "anim_collection/rainbowLoop.h"
#include "anim_collection/galacticNebula.h"
#include "anim_collection/pixelRushLoop.h"

// GalacticNebula* galacticNebula;
RainbowLoop* rainbowLoop = nullptr;
PixelRushLoop* pixelRushLoop = nullptr;

bool isLightOn = false;

void stopAllAnims() {
    animo.removeAllAnimations(false);
    animo.removeAllAnimationChains(false);
    if (rainbowLoop) {
        delete rainbowLoop;
        rainbowLoop = nullptr;
    }
    if (pixelRushLoop) {
        delete pixelRushLoop;
        pixelRushLoop = nullptr;
    }
}

void advanceAllAnims() {
    // galacticNebula->advance();
    if (pixelRushLoop) {
        pixelRushLoop->advance();
    }
}

// =======================================

void handleLightsOn()  {
    if (!isLightOn) {
        fadeBrightness(500, 0, 255);
        isLightOn = true;
    }
}
void handleLightsOff()  {
    if (isLightOn) {
        stopAllAnims();
        fadeBrightness(500, 255, 0);
        isLightOn = false;
    }
}

void handleLightToggle()  {
    if (!isLightOn) {
        setRGB(255, 255, 255);
        handleLightsOn();
    } else {
        handleLightsOff();
    }
}

void handleBedLight() {
    if (isLightOn) {
        stopAllAnims();
    }
    clear();
    for (u_int16_t i = 110; i < NUM_LEDS; i++) {
        setRGB(i, 255, 255, 255);
    }
    if (!isLightOn) {
        handleLightsOn();
    } else {
        setBrightness(255);
        show();
    }
}

void handleRainbow()  {
    if (!isLightOn) {
        handleLightsOn();
    } else {
        if (!rainbowLoop) {
            stopAllAnims();
        }
    }
    if (!rainbowLoop) {
        rainbowLoop = new RainbowLoop(6000);
        rainbowLoop->start();
    }
}

void handlePixelRush() {
    if (!isLightOn) {
        handleLightsOn();
    } else {
        if (!pixelRushLoop) {
            stopAllAnims();
        }
    }
    if (!pixelRushLoop) {
        pixelRushLoop = new PixelRushLoop();
        pixelRushLoop->start();
    }
}