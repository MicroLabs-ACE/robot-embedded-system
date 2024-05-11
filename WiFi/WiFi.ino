#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "LittleFS.h"

const char* ssid = "ESP8266AP";
const char* password = "password";

ESP8266WebServer server(80);

void handleRoot() {
  File htmlFile = LittleFS.open("/index.html", "r");
  if (!htmlFile) {
    server.send(404, "text/plain", "HTML File Not Found");
    return;
  }
  
  server.streamFile(htmlFile, "text/html");
  htmlFile.close();
}

void handleMove() {
  String requestBody = server.arg("plain");
  Serial.println("Received data: " + requestBody);
  server.send(200, "text/plain", "Received data: " + requestBody);
}

void setup() {
  Serial.begin(115200);
  
  if (!LittleFS.begin()) {
    Serial.println("Error while mounting LittleFS");
    return;
  }

  WiFi.softAP(ssid, password);

  server.on("/", HTTP_GET, handleRoot);
  server.on("/move", HTTP_POST, handleMove);

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
