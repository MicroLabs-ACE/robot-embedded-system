//
// Created on 6/27/24.
//

#include "NetworkSys.h"

NetworkSys::NetworkSys(const char *ssid, const char *password)
    : ssid(ssid), password(password) {
  // communicate state of machine
  Serial.println("Initializing networking");
  status = INITIALIZED;
  Serial.println("Network initialized");
}

NetworkSys::~NetworkSys() {
  status = UNINITIALIZED;
  Serial.println("Closing network system");
}

ENetworkState NetworkSys::connect() { return connect(ssid, password); }

ENetworkState NetworkSys::connect(const char *ssid, const char *password) {
  Serial.print("Connecting to ");
  Serial.println(ssid);
  // access point and station mode
  WiFi.mode(WIFI_AP_STA);
  WiFi.begin(ssid, password);
  // looping till we obtain connection
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1); // delay 1s before reconnecting
  }
  // connection successful
  status = CONNECTED;
  // print out local IP
  Serial.println(WiFi.localIP());
}
