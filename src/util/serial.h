#pragma once

#include <Arduino.h>

void initSerial() {
    Serial.begin(115200);
    delay(1500); // wait for serial to warm up
}