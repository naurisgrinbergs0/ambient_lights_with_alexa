// OTA helper for ESP8266
#pragma once
#include <Arduino.h>

// Initialize OTA service. Call after WiFi is connected.
void initOTA(const char* hostname = nullptr);

// Must be called frequently from loop to handle OTA events.
void handleOTA();
