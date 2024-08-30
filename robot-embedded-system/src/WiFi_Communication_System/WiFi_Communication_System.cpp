#include "WiFi_Communication_System.hpp"

bool WiFiCommunicationSystem::setStaticIPAddress(IPAddress localIPAddress,
                                                 IPAddress gateway,
                                                 IPAddress subnet) {
  return WiFi.config(localIPAddress, gateway, subnet);
}

bool WiFiCommunicationSystem::wifiAsStation(const char *ssid,
                                            const char *password) {
  int numberOfRetries = 0;
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED && numberOfRetries < 200) {
    delay(1000);
    numberOfRetries++;
  }
  return WiFi.status() == WL_CONNECTED;
}

bool WiFiCommunicationSystem::wifiAsAccessPoint(const char *ssid,
                                                const char *password) {
  return WiFi.softAP(ssid, password);
}

void WiFiCommunicationSystem::handleRoot(AsyncWebServerRequest *request) {
  IPAddress remoteIP = request->client()->remoteIP();
  DynamicJsonDocument responseJSON(1024);
  responseJSON["message"] = "Hello, world.";
  responseJSON["data"] = remoteIP.toString();
  String responseString;
  serializeJson(responseJSON, responseString);
  request->send(200, "application/json", responseString);
}

void WiFiCommunicationSystem::handleSample(AsyncWebServerRequest *request) {
  request->send(200, "text/plain", "This is a sample route");
}

void WiFiCommunicationSystem::onWebSocketEvent(AsyncWebSocket *server,
                                               AsyncWebSocketClient *client,
                                               AwsEventType type, void *arg,
                                               uint8_t *data, size_t len) {
  switch (type) {
  case WS_EVT_CONNECT:
    Serial.println("WebSocket client connected");
    break;
  case WS_EVT_DISCONNECT:
    Serial.println("WebSocket client disconnected");
    break;
  case WS_EVT_DATA:
    break;
  case WS_EVT_PONG:
  case WS_EVT_ERROR:
    break;
  }
}

void WiFiCommunicationSystem::runWebServer() {
  static AsyncWebServer webserver(80);
  static AsyncWebSocket websocket("/ws");
  websocket.onEvent(onWebSocketEvent);
  webserver.addHandler(&websocket);

  Route routes[] = {
      {"/", HTTP_GET, handleRoot},
      {"/sample", HTTP_GET, handleSample},
  };

  for (const auto &route : routes) {
    webserver.on(route.path, route.method, route.handler);
  }

  webserver.begin();
}

bool WiFiCommunicationSystem::connectWiFi(WiFiConnectionType connectionType,
                                          const char *ssid,
                                          const char *password) {
  bool result = false;
  switch (connectionType) {
  case STATION: {
    IPAddress localIPAddress(192, 168, 1, 184);
    IPAddress gateway(192, 168, 1, 1);
    IPAddress subnet(255, 255, 0, 0);
    bool isStaticIPAddress =
        setStaticIPAddress(localIPAddress, gateway, subnet);
    if (!isStaticIPAddress) {
      return false;
    }
    result = wifiAsStation(ssid, password);
  } break;
  case ACCESS_POINT:
    result = wifiAsAccessPoint(ssid, password);
    break;
  default:
    break;
  }
  if (result) {
    runWebServer();
  }
  return result;
}
