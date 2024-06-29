/**
 * NetworkSys.ino
 *
 *  Created on: 24.05.2015
 *
 */

#include <Arduino.h>
#include <WiFi.h>
#include "NetworkSys.h"

const char *ssid = "pan";
const char *password = "passwordx";

NetworkSys networkManager(ssid, password);

void setup() {
  Serial.begin(9600);
  networkManager.connect();
}

void loop() {
  // wait for WiFi connection
  Serial.println("Hello");
  delay(5000);
}
