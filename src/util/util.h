#pragma once
#include <Arduino.h>

bool isInRange(u_int8_t value, u_int8_t min, u_int8_t max) {
    return min <= value && value <= max;
}