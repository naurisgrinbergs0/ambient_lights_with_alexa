#include <fauxmoESP.h>

#define DEVICE00 "zero"

fauxmoESP fauxmo;

void setupWebserver() {
  fauxmo.addDevice(DEVICE00);

  fauxmo.setPort(80);
  fauxmo.enable(true);
  fauxmo.onSetState([](unsigned char device_id, const char * device_name, bool state, unsigned char value) {
      Serial.printf("[MAIN] Device #%d (%s) state: %s value: %d\n", device_id, device_name, state ? "ON" : "OFF", value);
    
      if (strcmp(device_name, DEVICE00)==0) {
          onDevice00Change();
      }
  });
}

void webserverListen() {
    fauxmo.handle();

  // outputs free heap
  // static unsigned long last = millis();
  // if (millis() - last > 5000) {
  //     last = millis();
  //     Serial.printf("[MAIN] Free heap: %d bytes\n", ESP.getFreeHeap());
  // }
}