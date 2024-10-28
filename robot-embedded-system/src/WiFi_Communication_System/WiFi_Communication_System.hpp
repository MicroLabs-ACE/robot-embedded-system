#ifndef WIFI_COMMUNICATION_SYSTEM_HPP
#define WIFI_COMMUNICATION_SYSTEM_HPP

#include <ArduinoJson.h>
#include <WebServer.h>
#include <WiFi.h>
#include <string>

enum WiFiConnectionType { STATION, ACCESS_POINT };

class WiFiCommunicationSystem {
public:
  static std::string lastReceivedData;
  bool connectWiFi(WiFiConnectionType connectionType, const char *ssid,
                   const char *password);
  std::string getLastReceivedData();
  static void loop();

private:
  bool setStaticIPAddress(IPAddress localIPAddress, IPAddress gateway,
                          IPAddress subnet);
  bool wifiAsStation(const char *ssid, const char *password);
  bool wifiAsAccessPoint(const char *ssid, const char *password);
  static void handleRoot();
  static void handleCommand();
  void runWebServer();

  static WebServer server;
};

#endif // WIFI_COMMUNICATION_SYSTEM_HPP
