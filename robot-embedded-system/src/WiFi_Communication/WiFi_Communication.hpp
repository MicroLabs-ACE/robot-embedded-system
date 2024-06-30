#ifndef WIFI_COMMUNICATION_HPP
#define WIFI_COMMUNICATION_HPP

#include <ArduinoJson.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <WiFi.h>

enum WiFiConnectionType {
  STATION,
  ACCESS_POINT
};

class WiFiCommunication {
private:
  static bool setStaticIPAddress(IPAddress localIPAddress, IPAddress gateway, IPAddress subnet);
  static bool wifiAsStation(const char *ssid, const char *password);
  static bool wifiAsAccessPoint(const char *ssid, const char *password);
  static void onWebSocketEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len);
  static void runWebServer();

  // Routes
  static void handleRoot(AsyncWebServerRequest *request);

public:
  static bool connectWiFi(WiFiConnectionType connectionType, const char *ssid, const char *password);
};

#endif  // WIFI_COMMUNICATION_HPP