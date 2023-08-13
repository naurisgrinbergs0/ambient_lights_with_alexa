#pragma once

#include "../lib/Animo/src/animo.h"

Animo animo = Animo();

#include "anim_collection/fadeBrightness.h"
#include "anim_collection/loopFadeBrightness.h"
#include "anim_collection/transitionToColor.h"
#include "anim_collection/loopRainbow.h"
#include "anim_collection/galacticNebula.h"

bool isLightOn = false;
void handleLightToggle()  {
    if (!isLightOn) {
        fadeBrightness(500, 0, 255);
        isLightOn = true;
    } else {
        fadeBrightness(500, 255, 0);
        isLightOn = false;
    }
}

void handleColorChange()  {
    setRGB(255, 255, 255);
    if (!isLightOn) {
        fadeBrightness(500, 0, 255);
        isLightOn = true;
    } else {
        fadeBrightness(500, 255, 0);
        isLightOn = false;
    }
}