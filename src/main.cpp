#include <ESP8266WiFi.h>
#include <fauxmoESP.h>
#include "util/serial.h"
#include "listeners.h"
#include "animation_collection.h"

fauxmoESP fauxmo;

void setupWifi() {
  WiFi.mode(WIFI_STA);
  Serial.printf("[WIFI] Connecting to %s ", WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
      Serial.print(".");
      delay(100);
  }
  Serial.println();
  Serial.printf("[WIFI] Connected. STATION Mode, SSID: %s, IP address: %s\n", WiFi.SSID().c_str(), WiFi.localIP().toString().c_str());
}

void setupFauxmo() {
  fauxmo.addDevice("light one");
  fauxmo.setPort(80);
  fauxmo.enable(true);
  fauxmo.onSetState([](unsigned char device_id, const char * device_name, bool state, unsigned char value) {
      Serial.printf("[MAIN] Device #%d (%s) state: %s value: %d\n", device_id, device_name, state ? "ON" : "OFF", value);

      if (strcmp(device_name, "light one")==0) {
          loopPulseBrigtness();
      }
  });
}

void setup() {
  // initialize serial
  initSerial();

  // initialize Arduino IoT Cloud
  // initCloud();
  setupWifi();
  setupFauxmo();

  // initialize strip
  initStrip();
}

Animator* Animator::instance = nullptr;

bool sw = true;
void loop() {
  if (sw) {
    // loopPulseBrigtness();

    sw = false;
  } 

  Animator::getInstance()->advanceAnimations();
  
  // fetchCloud();
  fauxmo.handle();
  // static unsigned long last = millis();
  // if (millis() - last > 5000) {
  //     last = millis();
  //     Serial.printf("[MAIN] Free heap: %d bytes\n", ESP.getFreeHeap());
  // }
}