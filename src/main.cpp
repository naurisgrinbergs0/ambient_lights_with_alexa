#include "util/serial.h"
#include "util/strip.h"
#include "util/wifi.h"
#include "util/server.h"
#include "handlers.h"

#define TEST_MODE 0
#define DEBUG_MODE 0

#define VIRTUAL_DEVICE_01 "Virtual Device 01"

void virtualDeviceStateChangeCallback(unsigned char device_id, const char * device_name, bool state, unsigned char value);
void test();

bool webserverInitialized = false;
Animation* 

void setup() {
  initSerial();
  initStrip();
  setupWifi();
}

void handleWifiConnected() {
  set(0, 255, 0);
  delay(500);
  clear();
  // set up webserver when wifi connected
  const char* deviceList[] = { VIRTUAL_DEVICE_01, nullptr };
  setupWebserver(deviceList, virtualDeviceStateChangeCallback);
  webserverInitialized = true;
}
void handleWifiConnecting() {
  int i = 0;
  bool turningOn = true;
  while (WiFi.status() != WL_CONNECTED) {
      Serial.print(".");
      set(i, turningOn ? 255 : 0, turningOn ? 187 : 0, 0);
      show();
      delay(100);
      i++;
      if (i >= NUM_LEDS) {
        i = 0;
        turningOn = !turningOn;
      }
  }
}

void loop() {
  // initialization
  if (isWifiConnected() && !webserverInitialized) {
    handleWifiConnected();
  } else {
    handleWifiConnecting();
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
}

void virtualDeviceStateChangeCallback(unsigned char device_id, const char * device_name, bool state, unsigned char value) {
  Serial.printf("[MAIN] Device #%d (%s) state: %s value: %d\n", device_id, device_name, state ? "ON" : "OFF", value);

  if (strcmp(device_name, VIRTUAL_DEVICE_01) == 0) {
      if (value < 10) {
        handleDangerAction();
      }
  }
}



bool sw = true;
void test() {
  if (sw) {
    loopFadeBrightness();

    sw = false;
  } 
}