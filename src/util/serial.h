#pragma once

#include <Arduino.h>

void initSerial() {
    Serial.begin(921600);
    delay(1500); // wait for serial to warm up
}

void log() {
    Serial.println();
}

template<typename T, typename... Args>
void log(T arg, Args... args) {
    Serial.print(arg);
    log(args...);
}