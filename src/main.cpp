#include <WiFiManager.h>

#include <BasicOTA.hpp>


BasicOTA OTA;

void setup() {
  Serial.begin(115200);

  Serial.println("start Wifimanager");
  WiFiManager wifiManager;
  while (!wifiManager.autoConnect("Stairs")) {
    Serial.println("wifi retry");
  }
  Serial.print("wifi connected, IP address: ");
  Serial.println(WiFi.localIP());

  Serial.println("start OTA");
  OTA.begin();

  Serial.println("done");
}

void loop() {
  OTA.handle();
}