#ifndef WIFI_COMMUNICATION_HPP
#define WIFI_COMMUNICATION_HPP

#include "WiFiRouter.hpp"
#include <WiFi.h>

enum WiFiConnectionType { STATION, ACCESS_POINT };

class WiFiCommunication {
public:
  bool setStaticIPAddress(IPAddress localIPAddress, IPAddress gateway,
                          IPAddress subnet);
  bool wifiAsStation(const char *ssid, const char *password);
  bool wifiAsAccessPoint(const char *ssid, const char *password);
  bool connectWiFi(WiFiConnectionType connectionType, const char *ssid,
                   const char *password);

private:
  WiFiRouter router;
};

#endif // WIFI_COMMUNICATION_HPP
