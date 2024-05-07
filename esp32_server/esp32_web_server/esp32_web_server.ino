#include <WiFi.h>
#include <WebServer.h>

const char *ssid = "ESP32_SERVER";
const char *password = "server2018";

IPAddress local_ip(192,168,1,1);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

WebServer server(80);

void handleRoot() {
  server.send(200, "text/plain", "Hello from ESP32!");
}

void setup() {
  Serial.begin(115200);
  
  // Set up the WiFi AP
  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(local_ip, gateway, subnet);
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