#include "util/util.h"
#include "util/serial.h"
#include "util/strip.h"
#include "util/wifi.h"
#include "util/server.h"
#include "handlers.h"

#define SET_UP_WIFI_AND_SERVER 1
#define TEST_MODE 0

#define VIRTUAL_DEVICE_01 "Virtual Device 01"

void virtualDeviceStateChangeCallback(unsigned char device_id, const char * device_name, bool state, unsigned char value);
void test();

bool webserverInitialized = false;

AnimationChain* fadeChain;
void setup() {
  initSerial();
  initStrip();

  if (SET_UP_WIFI_AND_SERVER) {
    // initialization animation
    setRGB(0, 255, 187, 0, false);
    fadeChain = loopFadeBrightness(200, 200, 0, 255);
    setupWifi();
  }
}

void handleWifiConnected() {
  // set up webserver when wifi connected
  const char* deviceList[] = { VIRTUAL_DEVICE_01, nullptr };
  setupWebserver(deviceList, virtualDeviceStateChangeCallback);
  webserverInitialized = true;

  animo.removeAnimationChain(fadeChain, false, false);
  setBrightness(255);
  setRGB(0, 0, 255, 0, true);
  delay(800);
  setBrightness(0, true);
}

void loop() {
  // initialization
  if (isWifiConnected() && !webserverInitialized) {
    handleWifiConnected();
  } 
  
  // listen for requests
  if (isWifiConnected() && webserverInitialized) {
    webserverListen();
  }
  // advance animations
  animo.advanceAnimations();

  // testing
  if (TEST_MODE) {
    test();
  }

  advanceAllAnims();
}

void virtualDeviceStateChangeCallback(unsigned char device_id, const char * device_name, bool state, unsigned char value) {
  value = map(value, 0, 255, 0, 100);
  Serial.printf("[MAIN] Device #%d (%s) state: %s value: %d\n", device_id, device_name, state ? "ON" : "OFF", value);

  if (strcmp(device_name, VIRTUAL_DEVICE_01) == 0) {
      if (isInRange(value, 1, 5)) {
        setRGB(255, 255, 255);
        handleLightsOn();
      } else if (isInRange(value, 6, 10)) {
        handleLightsOff();
      } else if (isInRange(value, 11, 15)) {
        handleLightToggle();
      } else if (isInRange(value, 16, 20)) {
        handleBedLight();
      } else if (isInRange(value, 21, 25)) {
        handleRainbow();
      } else if (isInRange(value, 26, 30)) {
        handlePixelRush();
      }
  }
}



bool sw = true;
void test() {
  // delay(300);
  if (sw) {
    setBrightness(255);
    clear(true);

    // galacticNebula->start();

    sw = false;
  } 
}