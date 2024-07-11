#ifndef WIFI_COMMUNICATION_HPP
#define WIFI_COMMUNICATION_HPP

#include <ArduinoJson.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <WiFi.h>

enum WiFiConnectionType
{
  STATION,
  ACCESS_POINT
};

// Enum to represent different HTTP methods
// This allows us to specify the method for each route
enum WebRequestMethod
{
  HTTP_GET,
  HTTP_POST,
  HTTP_DELETE,
  HTTP_PUT,
  HTTP_PATCH,
  HTTP_HEAD,
  HTTP_OPTIONS
};

// Typedef for a pointer to a static function that handles web requests
// This matches the signature of our handler functions (e.g., handleRoot, handleSa
typedef void (*ArRequestHandlerFunction)(AsyncWebServerRequest *request);

class WiFiCommunication
{
private:
  static bool setStaticIPAddress(IPAddress localIPAddress, IPAddress gateway, IPAddress subnet);
  static bool wifiAsStation(const char *ssid, const char *password);
  static bool wifiAsAccessPoint(const char *ssid, const char *password);
  static void onWebSocketEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len);
  static void runWebServer();

  // Routes
  static void handleRoot(AsyncWebServerRequest *request);
  static void handleSample(AsyncWebServerRequest *request); // New route handler

public:
  static bool connectWiFi(WiFiConnectionType connectionType, const char *ssid, const char *password);
};

#endif // WIFI_COMMUNICATION_HPP