#ifndef WIFI_ROUTER_HPP
#define WIFI_ROUTER_HPP

#include <ArduinoJson.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <WiFi.h>

typedef void (*ArRequestHandlerFunction)(AsyncWebServerRequest *request);

struct Router {
  const char *path;
  ArRequestHandlerFunction handler;
};

class WiFiRouter {
public:
  WiFiRouter();
  Router *getRouters();
  void runWebServer();

private:
  static void handleRoot(AsyncWebServerRequest *request);
  static void handleSample(AsyncWebServerRequest *request);
  AsyncWebServer *webserver;
  AsyncWebSocket *websocket;
};

#endif // WIFI_ROUTER_HPP
