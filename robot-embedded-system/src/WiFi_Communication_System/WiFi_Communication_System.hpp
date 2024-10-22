#ifndef WIFI_COMMUNICATION_SYSTEM_HPP
#define WIFI_COMMUNICATION_SYSTEM_HPP

#include <Arduino.h>
#include <ArduinoJson.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <WiFi.h>
#include <string>

enum WiFiConnectionType { STATION, ACCESS_POINT };

struct Route {
  const char *path;
  WebRequestMethodComposite method;
  ArRequestHandlerFunction handler;
};

class WiFiCommunicationSystem {
public:
  static bool connectWiFi(WiFiConnectionType connectionType, const char *ssid,
                          const char *password);
  static std::string getLastReceivedData();

private:
  static bool setStaticIPAddress(IPAddress localIPAddress, IPAddress gateway,
                                 IPAddress subnet);
  static bool wifiAsStation(const char *ssid, const char *password);
  static bool wifiAsAccessPoint(const char *ssid, const char *password);
  static void onWebSocketEvent(AsyncWebSocket *server,
                               AsyncWebSocketClient *client, AwsEventType type,
                               void *arg, uint8_t *data, size_t len);
  static void runWebServer();
  static void handleWebSocketData(void *arg, uint8_t *data, size_t len);
  static void handleRoot(AsyncWebServerRequest *request);

  static std::string lastReceivedData;
};

#endif // WIFI_COMMUNICATION_SYSTEM_HPP
