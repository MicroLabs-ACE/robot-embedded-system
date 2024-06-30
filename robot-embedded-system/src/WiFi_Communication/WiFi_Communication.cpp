#include "WiFi_Communication.hpp"

bool WiFiCommunication::setStaticIPAddress(IPAddress localIPAddress, IPAddress gateway, IPAddress subnet) {
  return WiFi.config(localIPAddress, gateway, subnet);
}

bool WiFiCommunication::wifiAsStation(const char *ssid, const char *password) {
  int numberOfRetries = 0;
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED && numberOfRetries < 200) {
    delay(1000);
    numberOfRetries++;
  }

  return WiFi.status() == WL_CONNECTED;
}

bool WiFiCommunication::wifiAsAccessPoint(const char *ssid, const char *password) {
  return WiFi.softAP(ssid, password);
}

void WiFiCommunication::handleRoot(AsyncWebServerRequest *request) {
  IPAddress remoteIP = request->client()->remoteIP();
  DynamicJsonDocument responseJSON(1024);
  responseJSON["message"] = "Hello, world.";
  responseJSON["data"] = remoteIP.toString();

  String responseString;
  serializeJson(responseJSON, responseString);
  request->send(200, "application/json", responseString);
}

void WiFiCommunication::onWebSocketEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len) {
  switch (type) {
    case WS_EVT_CONNECT:
      // Handle websocket event connect event
      break;

    case WS_EVT_DISCONNECT:
      // Handle websocket event disconnect event
      break;

    case WS_EVT_DATA:
      // Handle websocket event data event
      break;

    case WS_EVT_PONG:
    case WS_EVT_ERROR:
    default:
      break;
  }
}

void WiFiCommunication::runWebServer() {
  static AsyncWebServer webserver(80);
  static AsyncWebSocket websocket("/ws");
  websocket.onEvent(WiFiCommunication::onWebSocketEvent);
  webserver.addHandler(&websocket);

  webserver.on("/", HTTP_GET, WiFiCommunication::handleRoot);

  webserver.begin();
}

bool WiFiCommunication::connectWiFi(WiFiConnectionType connectionType, const char *ssid, const char *password) {
  bool result = false;

  switch (connectionType) {
    case STATION:
      {
        IPAddress localIPAddress(192, 168, 1, 184);
        IPAddress gateway(192, 168, 1, 1);
        IPAddress subnet(255, 255, 0, 0);

        bool isStaticIPAddress = WiFiCommunication::setStaticIPAddress(localIPAddress, gateway, subnet);
        if (!isStaticIPAddress) {
          return false;
        }

        result = WiFiCommunication::wifiAsStation(ssid, password);
      }
      break;

    case ACCESS_POINT:
      result = WiFiCommunication::wifiAsAccessPoint(ssid, password);
      break;

    default:
      break;
  }

  if (result) {
    WiFiCommunication::runWebServer();
  }

  return result;
}