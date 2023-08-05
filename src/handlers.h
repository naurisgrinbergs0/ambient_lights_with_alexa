#pragma once

#include "animCollection.h"

bool isLightOn = false;
void handleDangerAction()  {
    set(255, 0, 0);
    if (!isLightOn) {
        fadeInBrightness();
        isLightOn = true;
    } else {
        fadeOutBrightness();
        isLightOn = false;
    }
}