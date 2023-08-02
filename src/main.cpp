#include "animation/animator.h"
#include "animation_collection.h"
#include "listeners.h"
#include "util/serial.h"
#include "util/wifi.h"
#include "util/server.h"

#define TEST_MODE 0
#define DEBUG_MODE 0

Animator* Animator::instance = nullptr;

void test();

void setup() {
  // initialize serial
  initSerial();

  // initialize wifi & start webserver
  setupWifi();
  setupWebserver();

  // initialize strip
  initStrip();
}

void loop() {
  if (TEST_MODE) {
    test();
  }

  Animator::getInstance()->advanceAnimations();
  webserverListen();
}

bool sw = true;
void test() {
  if (sw) {
    loopPulseBrigtness();

    sw = false;
  } 
}