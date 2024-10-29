#ifndef WIFI_COMMUNICATION_SYSTEM_HPP
#define WIFI_COMMUNICATION_SYSTEM_HPP

#include <ArduinoJson.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <WiFi.h>
#include <string>

enum WiFiConnectionType { STATION, ACCESS_POINT };

class WiFiCommunicationSystem {
public:
  bool connectWiFi(WiFiConnectionType connectionType, const char *ssid,
                   const char *password);
  std::string getCommand();
  static void loop();

private:
  bool setStaticIPAddress(IPAddress localIPAddress, IPAddress gateway,
                          IPAddress subnet);
  bool wifiAsStation(const char *ssid, const char *password);
  bool wifiAsAccessPoint(const char *ssid, const char *password);
  static void handleCommand();
  void initialiseWebServer();

  static AsyncWebServer server;
  static AsyncWebSocket socket;

  static std::string command;
};

#endif // WIFI_COMMUNICATION_SYSTEM_HPP
