#include "WiFi_Communication.hpp"

void setup() {
  Serial.begin(115200);

  const char *ssid = "Microlab";
  const char *password = "Engin33r";

  bool result = WiFiCommunication::connectWiFi(WiFiConnectionType::STATION, ssid, password);
  Serial.print("Connection: ");
  Serial.println(result);
}

void loop() {}