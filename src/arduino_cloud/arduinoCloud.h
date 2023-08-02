#include "arduino_cloud/thingProperties.h"

void initCloud() {
    initProperties();

    ArduinoCloud.begin(ArduinoIoTPreferredConnection);
    setDebugMessageLevel(4);
    ArduinoCloud.printDebugInfo();
}

void fetchCloud() {
    ArduinoCloud.update();
}