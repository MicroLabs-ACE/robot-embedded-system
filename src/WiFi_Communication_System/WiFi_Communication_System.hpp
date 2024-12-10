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
  void loop();

private:
  bool setStaticIPAddress(IPAddress localIPAddress, IPAddress gateway,
                          IPAddress subnet);
  bool wifiAsStation(const char *ssid, const char *password);
  bool wifiAsAccessPoint(const char *ssid, const char *password);
  void onWebsocketEvent(AsyncWebSocket *server, AsyncWebSocketClient *client,
                        AwsEventType type, void *arg, uint8_t *data,
                        size_t len);
  void handleWebsocketData(void *arg, uint8_t *data, size_t len);
  void initialiseWebServer();

  AsyncWebServer server{80};
  AsyncWebSocket socket{"/ws"};

  static std::string command;
};

#endif // WIFI_COMMUNICATION_SYSTEM_HPP
