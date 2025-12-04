#include "util/util.h"
#include "util/serial.h"
#include "util/strip.h"
#include "util/wifi.h"
#include "util/server.h"
#include "util/ota.h"
#include "handlers.h"

#define SET_UP_WIFI_AND_SERVER 1
#define TEST_MODE 0

#define VIRTUAL_DEVICE_01 "Ambient Lights"

void virtualDeviceStateChangeCallback(unsigned char device_id, const char * device_name, bool state, unsigned char value);
void test();

bool webserverInitialized = false;

PulseBrightnessLoop* initAnim = new PulseBrightnessLoop();
void setup() {
  initSerial();
  initStrip();
  initHandlers();

  if (SET_UP_WIFI_AND_SERVER) {
    // initialization animation
    setRGB(0, 255, 187, 0, false);
    initAnim->setFadeInDuration(200);
    initAnim->setFadeOutDuration(200);
    initAnim->setStartBrightness(0);
    initAnim->setEndBrightness(255);
    initAnim->start();
    setupWifi();
  }
}

void handleWifiConnected() {
  // set up webserver when wifi connected
  const char* deviceList[] = { VIRTUAL_DEVICE_01, nullptr };
  setupWebserver(deviceList, virtualDeviceStateChangeCallback);
  webserverInitialized = true;

  // start OTA service so we can upload firmware over WiFi
  initOTA();

  animo.removeAllAnimationChains(false);
  delete initAnim;
  initAnim = nullptr;

  setBrightness(255);
  setRGB(0, 0, 255, 0, true);
  delay(800);
  setRGB(0, 0, 0);
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
  if ((TEST_MODE && (SET_UP_WIFI_AND_SERVER && isWifiConnected() && webserverInitialized)) || (TEST_MODE && !SET_UP_WIFI_AND_SERVER)) {
    test();
  }

  // handle OTA updates
  handleOTA();

  advanceAllAnims();
}

void virtualDeviceStateChangeCallback(unsigned char device_id, const char * device_name, bool state, unsigned char value) {
  value = map(value, 0, 255, 0, 100);
  Serial.printf("[MAIN] Device #%d (%s) state: %s value: %d\n", device_id, device_name, state ? "ON" : "OFF", value);

  if (strcmp(device_name, VIRTUAL_DEVICE_01) == 0) {
      if (isInRange(value, 1, 5)) { // Sets color to white and turns the strip on - 3
        setRGB(255, 255, 255);
        handleLightsOn();
      } else if (isInRange(value, 6, 10)) { // Turns the strip off - 8
        handleLightsOff();
      } else if (isInRange(value, 11, 15)) { // Toggles the led strip - 13
        handleLightToggle();
      } else if (isInRange(value, 16, 20)) { // Night light - 18
        handleNightLight();
      } else if (isInRange(value, 21, 25)) { // Infinite rainbow animation - 23
        handleRainbow();
      } else if (isInRange(value, 26, 30)) { // Pixel rush animation - 28
        handlePixelRush();
      } else if (isInRange(value, 31, 35)) { // Danger animation - 33
        handleDanger();
      } else if (isInRange(value, 36, 40)) { // Netflix and Chill mood - 38
        handleNetflixAndChill();
      } else if (isInRange(value, 41, 45)) { // Restarts the microcontroller - 43
        ESP.restart();
      } else if (isInRange(value, 46, 50)) { // Christmas mood - 48
        handleChristmasMood();
      }
  }
}



bool sw = true;
void test() {
  // delay(300);
  if (sw) {
    handleChristmasMood();

    sw = false;
  } 
}