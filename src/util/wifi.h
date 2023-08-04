#include <Arduino.h>
#include <ESP8266WiFi.h>

void setupWifi() {
  WiFi.mode(WIFI_STA);
  Serial.printf("[WIFI] Connecting to %s ", WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.println();
  Serial.printf("[WIFI] Connected. STATION Mode, SSID: %s, IP address: %s\n", WiFi.SSID().c_str(), WiFi.localIP().toString().c_str());
}

bool isWifiConnected() {
  return WiFi.status() == WL_CONNECTED;
}