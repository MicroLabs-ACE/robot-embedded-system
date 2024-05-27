#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <WiFi.h>
#include "LittleFS.h"

struct DCMotor {
  int input0;
  int input1;
  int enable;
};

enum MotorRotation {
  CW,
  AntiCW,
  Stop,
};

int highSpeed = 153;
int lowSpeed = 77;
int speedLevel = 3;

DCMotor motorLeft;
DCMotor motorRight;

void setDCMotor(DCMotor &dcMotor, int input0, int input1, int enable) {
  dcMotor.input0 = input0;
  dcMotor.input1 = input1;
  dcMotor.enable = enable;

  pinMode(dcMotor.input0, OUTPUT);
  pinMode(dcMotor.input1, OUTPUT);
  pinMode(dcMotor.enable, OUTPUT);
}

void setMotorData(DCMotor &dcMotor, MotorRotation rotation, int speed) {
  switch (rotation) {
    case CW:
      digitalWrite(dcMotor.input0, HIGH);
      digitalWrite(dcMotor.input1, LOW);
      break;

    case AntiCW:
      digitalWrite(dcMotor.input0, LOW);
      digitalWrite(dcMotor.input1, HIGH);
      break;

    case Stop:
      digitalWrite(dcMotor.input0, LOW);
      digitalWrite(dcMotor.input1, LOW);
      break;

    default:
      break;
  }

  analogWrite(dcMotor.enable, speed);
}

void controlMotor(char direction[3]) {
  Serial.println(direction);
  if (strcmp(direction, "OO") == 0) {
    Serial.println("Origin");
    setMotorData(motorLeft, MotorRotation::Stop, 0);
    setMotorData(motorRight, MotorRotation::Stop, 0);
  } else if (strcmp(direction, "NO") == 0) {
    Serial.println("North");
    setMotorData(motorLeft, MotorRotation::CW, highSpeed);
    setMotorData(motorRight, MotorRotation::CW, highSpeed);
  } else if (strcmp(direction, "SO") == 0) {
    Serial.println("South");
    setMotorData(motorLeft, MotorRotation::AntiCW, highSpeed);
    setMotorData(motorRight, MotorRotation::AntiCW, highSpeed);
  } else if (strcmp(direction, "OW") == 0) {
    Serial.println("West");
    setMotorData(motorLeft, MotorRotation::Stop, 0);
    setMotorData(motorRight, MotorRotation::CW, highSpeed);
  } else if (strcmp(direction, "OE") == 0) {
    Serial.println("East");
    setMotorData(motorLeft, MotorRotation::CW, highSpeed);
    setMotorData(motorRight, MotorRotation::Stop, 0);
  } else if (strcmp(direction, "NE") == 0) {
    Serial.println("NorthEast");
    setMotorData(motorLeft, MotorRotation::CW, highSpeed);
    setMotorData(motorRight, MotorRotation::CW, lowSpeed);
  } else if (strcmp(direction, "NW") == 0) {
    Serial.println("NorthWest");
    setMotorData(motorLeft, MotorRotation::CW, lowSpeed);
    setMotorData(motorRight, MotorRotation::CW, highSpeed);
  } else if (strcmp(direction, "SE") == 0) {
    Serial.println("SouthEast");
    setMotorData(motorLeft, MotorRotation::AntiCW, highSpeed);
    setMotorData(motorRight, MotorRotation::AntiCW, lowSpeed);
  } else if (strcmp(direction, "SW") == 0) {
    Serial.println("SouthWest");
    setMotorData(motorLeft, MotorRotation::AntiCW, lowSpeed);
    setMotorData(motorRight, MotorRotation::AntiCW, highSpeed);
  }
}

const char *ssid = "Microlab";
const char *password = "Engin33r";

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

String indexHTML;
String images[] = {
  "/images/up_outlined.png",
  "/images/down_outlined.png",
  "/images/left_outlined.png",
  "/images/right_outlined.png",
  "/images/up_filled.png",
  "/images/down_filled.png",
  "/images/left_filled.png",
  "/images/right_filled.png",
};
const int numberOfImages = 8;

void readIndexHTMLFile() {
  File indexHTMLFile = LittleFS.open("/index.html", "r");
  if (!indexHTMLFile) {
    Serial.println("Failed to open file for reading.");
    return;
  }

  indexHTML = indexHTMLFile.readString();
  indexHTMLFile.close();
}

void setSpeed(int speedLevel) {
  switch (speedLevel) {
    case 1:
      highSpeed = 51;
      lowSpeed = 26;
      break;

    case 2:
      highSpeed = 102;
      lowSpeed = 51;
      break;

    case 3:
      highSpeed = 153;
      lowSpeed = 77;
      break;

    case 4:
      highSpeed = 204;
      lowSpeed = 102;
      break;

    case 5:
      highSpeed = 255;
      lowSpeed = 128;
      break;

    default:
      break;
  }
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
      char direction[3];
      direction[0] = (char)data[0];
      direction[1] = (char)data[2];
      direction[2] = '\0';
      speedLevel = (char)data[4] - '0';
      Serial.println(speedLevel);
      setSpeed(speedLevel);
      controlMotor(direction);
      break;

    case WS_EVT_PONG:
    case WS_EVT_ERROR:
    default:
      break;
  }
}

void handleRoot(AsyncWebServerRequest *request) {
  IPAddress remoteIP = request->client()->remoteIP();
  Serial.println("[" + remoteIP.toString() + "] HTTP GET request of " + request->url());
  request->send(200, "text/html", indexHTML);
}

void handleImage(AsyncWebServerRequest *request, const String &filename) {
  File file = LittleFS.open(filename, "r");
  if (!file) {
    request->send(404, "text/plain", "Image not found");
    return;
  }
  String contentType = "image/png";
  request->send(file, contentType);
  file.close();
}

void handleNotFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found.");
}

void setup() {
  setDCMotor(motorLeft, 18, 19, 21);
  setDCMotor(motorRight, 27, 26, 25);

  Serial.begin(115200);

  if (!LittleFS.begin()) {
    Serial.println("Error mounting LittleFS.");
    while (1)
      ;
  }

  // WiFi.softAP(ssid, password);
  // Serial.println();
  // Serial.print("IP address: ");
  // Serial.println(WiFi.softAPIP());

  WiFi.begin(ssid, password);  // Connect to the network
  Serial.print("Connecting to ");
  Serial.print(ssid);

  while (WiFi.status() != WL_CONNECTED) {  // Wait for the Wi-Fi to connect
    delay(500);
    Serial.print('.');
  }

  Serial.println('\n');
  Serial.println("Connection established!");
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());

  ws.onEvent(handleWebSocketEvent);
  server.addHandler(&ws);

  readIndexHTMLFile();
  server.on("/", HTTP_GET, handleRoot);
  for (int i = 0; i < numberOfImages; ++i) {
    String path = images[i];
    server.on(path.c_str(), HTTP_GET, [path](AsyncWebServerRequest *request) {
      handleImage(request, path);
    });
  }
  server.onNotFound(handleNotFound);
  server.begin();
}

void loop() {}
