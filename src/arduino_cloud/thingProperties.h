#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>

void onColoredLightChange();
void onIsOnChange();

CloudColoredLight coloredLight;
CloudSwitch isOn;

void initProperties(){
  ArduinoCloud.setBoardId(CLOUD_DEVICE_LOGIN_NAME);
  ArduinoCloud.setSecretDeviceKey(CLOUD_DEVICE_KEY);

  ArduinoCloud.addProperty(coloredLight, READWRITE, ON_CHANGE, onColoredLightChange);
  ArduinoCloud.addProperty(isOn, READWRITE, ON_CHANGE, onIsOnChange);
}

WiFiConnectionHandler ArduinoIoTPreferredConnection(WIFI_SSID, WIFI_PASSWORD);
