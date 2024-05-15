#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <WiFi.h>

#include "LittleFS.h"

struct DCMotor {
  int input0;
  int input1;
  int enable;
}

enum MotorRotation {
  CW,
  AntiCW,
  Stop,
};

enum MotorDirection {
  NORTH,
  SOUTH,
  EAST,
  WEST,
  NORTHEAST,
  NORTHWEST,
  SOUTHEAST,
  SOUTHWEST,
};

int speed = 127;

const char *ssid = "Locomotor Model A";
const char *password = "password1234";

AsyncWebServer server(80);
AsyncWebSocket socket("/ws");

String indexHTML;

void getIndexHTMLFile() {
  File indexHTMLFile = LittleFS.open("/index.html", "r");
  if (!indexHTMLFile) {
    Serial.println("Failed to open file for reading.");
    return;
  }

  indexHTML = indexHTMLFile.readString();
  indexHTMLFile.close();
}

void handleWebSocketEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len) {
  switch (type) {
    case WS_EVT_CONNECT:
      Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
      break;

    case WS_EVT_DISCONNECT:
      Serial.printf("WebSocket client #%u disconnected\n", client->id());
      break;

    case WS_EVT_DATA:
      Serial.printf("Received WebSocket message from client #%u: ", client->id());
      char dirNorthSouth = (char)data[0];
      char dirEastWest = (char)data[2];
      break;

    case WS_EVT_PONG:
    case WS_EVT_ERROR:
      break;
  }
}

void handleRoot(AsyncWebServerRequest *request) {
  IPAddress remoteIP = request->client()->remoteIP();
  Serial.println("[" + remoteIP.toString() + "] HTTP GET request of " + request->url());
  request->send(200, "text/html", indexHTML);
}

void handleNotFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found.");
}

void setup() {
  DCMotor motorLeft;
  DCMotor motorRight;

  setDCMotor(motorLeft, 18, 19, 21);
  setDCMotor(motorRight, 27, 26, 25);

  Serial.begin(115200);

  if (!LittleFS.begin()) {
    Serial.println("Error mounting LittleFS.");
    while (1)
      ;
  }

  getIndexHTMLFile();

  WiFi.softAP(ssid, password);
  Serial.println();
  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP());

  socket.onEvent(handleWebSocketEvent);
  server.addHandler(&socket);

  server.on("/", HTTP_GET, handleRoot);
  server.onNotFound(handleNotFound);

  server.begin();
}

void loop() {}