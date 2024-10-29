#include "WiFi_Communication_System.hpp"

std::string WiFiCommunicationSystem::command = "";
AsyncWebServer WiFiCommunicationSystem::server(80);
AsyncWebSocket WiFiCommunicationSystem::socket("/");

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
  while (WiFi.status() != WL_CONNECTED && numberOfRetries < 20) {
    delay(1000);
    numberOfRetries++;
  }
  return WiFi.status() == WL_CONNECTED;
}

bool WiFiCommunicationSystem::wifiAsAccessPoint(const char *ssid,
                                                const char *password) {
  return WiFi.softAP(ssid, password);
}

void WiFiCommunicationSystem::initialiseWebServer() {
  socket.onEvent(onEvent);
  server.addHandler(&socket);
  server.begin();
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
    initialiseWebServer();
  }
  return result;
}

void WiFiCommunicationSystem::onEvent(AsyncWebSocket *server,
                                      AsyncWebSocketClient *client,
                                      AwsEventType type, void *arg,
                                      uint8_t *data, size_t len) {
  switch (type) {
  case WS_EVT_CONNECT:
    Serial.printf("WebSocket client #%u connected from %s\n", client->id(),
                  client->remoteIP().toString().c_str());
    break;
  case WS_EVT_DISCONNECT:
    Serial.printf("WebSocket client #%u disconnected\n", client->id());
    break;
  case WS_EVT_DATA:
    handleWebsocketData(arg, data, len);
    break;
  case WS_EVT_PONG:
  case WS_EVT_ERROR:
    break;
  }
}

void WiFiCommunicationSystem::handleWebsocketData(void *arg, uint8_t *data,
                                                  size_t len) {
  AwsFrameInfo *info = (AwsFrameInfo *)arg;
  if (info->final && info->index == 0 && info->len == len &&
      info->opcode == WS_TEXT) {
    data[len] = 0;
    command = std::string((char *)data);
  }
}

std::string WiFiCommunicationSystem::getCommand() { return command; }

void WiFiCommunicationSystem::loop() { socket.cleanupClients(); }
