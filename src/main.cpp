#include <WiFiManager.h>
#include <arduino.h>

#include <BasicOTA.hpp>

#include "light/light.h"
#include "pin.h"
#include "secrets.h"

BasicOTA OTA;

void setup() {
  Serial.begin(115200);

  Serial.println("start Wifimanager");
  WiFiManager wifiManager;
  while (!wifiManager.autoConnect("Stairs")) {
    Serial.println("wifi retry");
  }

  Serial.println("setup pins");
  setUpPins();

  Serial.println("setup leds");
  initLight();

  Serial.println("start OTA");
  OTA.begin();

  Serial.println("started");
  Serial.println("------------------------------------");
}

void loop() {
  OTA.handle();

  processLeds();
}