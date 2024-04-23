// #include <ESP8266WiFi.h>

// const char *ssid = "Microlabs";
// const char *pass = "Engin33r";

// void setup() {
//   Serial.begin(9600);
//   delay(10);

//   Serial.println("Connecting to ");
//   Serial.println(ssid);
//   WiFi.begin(ssid, pass);
//   while (WiFi.status() != WL_CONNECTED) {
//     delay(500);
//     Serial.print(".");
//   }
//   Serial.println("");
//   Serial.println("WiFi connected");
//   Serial.println('\n');
//   Serial.println("Connection established!");
//   Serial.print("IP address:\t");
//   Serial.println(WiFi.localIP());
// }

// void loop() {
// }

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "Robot";
const char* password = "12345678";

IPAddress local_ip(192, 168, 1, 1);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

ESP8266WebServer server(80);

void handleRoot() {
  server.send(200, "text/plain", "Hello, world!");
}

void setup() {
  Serial.begin(115200);

  // Set static IP configuration
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  WiFi.softAP(ssid, password);

  Serial.println("WiFi AP started");

  // Route for root URL
  server.on("/", handleRoot);

  // Start HTTP server
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}