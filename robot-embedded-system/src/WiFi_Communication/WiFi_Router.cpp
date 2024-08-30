#include "WiFi_Router.hpp"
#include "WiFiRouter.hpp"

WiFiRouter::WiFiRouter() {
  webserver = new AsyncWebServer(80);
  websocket = new AsyncWebSocket("/ws");

  websocket->onEvent([](AsyncWebSocket *server, AsyncWebSocketClient *client,
                        AwsEventType type, void *arg, uint8_t *data,
                        size_t len) {
    switch (type) {
    case WS_EVT_CONNECT:
      break;

    case WS_EVT_DISCONNECT:
      break;

    case WS_EVT_DATA:
      break;

    case WS_EVT_PONG:
    case WS_EVT_ERROR:
    default:
      break;
    }
  });

  webserver->addHandler(websocket);
}

Router *WiFiRouter::getRouters() {
  static Router routes[] = {
      {"/", WiFiRouter::handleRoot},
      {"/sample", WiFiRouter::handleSample},
  };
  return routes;
}

void WiFiRouter::handleRoot(AsyncWebServerRequest *request) {
  IPAddress remoteIP = request->client()->remoteIP();
  DynamicJsonDocument responseJSON(1024);
  responseJSON["message"] = "Hello, world.";
  responseJSON["data"] = remoteIP.toString();

  String responseString;
  serializeJson(responseJSON, responseString);
  request->send(200, "application/json", responseString);
}

void WiFiRouter::handleSample(AsyncWebServerRequest *request) {
  request->send(200, "text/plain", "This is a sample route");
}

void WiFiRouter::runWebServer() {
  Router *routes = getRouters();
  for (const auto &route : routes) {
    webserver->on(route.path, HTTP_GET, route.handler);
  }

  webserver->begin();
}
