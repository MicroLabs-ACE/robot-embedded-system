#include <WiFi.h>
#include <WebServer.h>

const char *ssid = "MyESP32AP";
const char *password = "password123";

WebServer server(80);

void handleRoot() {
  server.send(200, "text/plain", "Hello from ESP32!");
}

void setup() {
  Serial.begin(115200);
  
  // Set up the WiFi AP
  WiFi.softAP(ssid, password);
  
  Serial.println("WiFi AP started");
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());
  
  // Route for root
  server.on("/", handleRoot);

  // Start server
  server.begin();
}

void loop() {
  server.handleClient();
}
