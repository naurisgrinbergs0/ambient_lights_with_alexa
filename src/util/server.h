#include <fauxmoESP.h>

typedef void (*StateChangeCallback)(unsigned char device_id, const char * device_name, bool state, unsigned char value);

fauxmoESP fauxmo;

void setupWebserver(const char* deviceList[], StateChangeCallback stateChangeCallback) {
  for (u_int8_t i = 0; deviceList[i]; i++) {
      fauxmo.addDevice(deviceList[i]);
  }

  fauxmo.setPort(80);
  fauxmo.enable(true);
  fauxmo.onSetState(stateChangeCallback);
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