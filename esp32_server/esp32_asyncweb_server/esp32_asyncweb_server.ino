#include <WiFi.h>
#include <ESPAsyncWebServer.h>

const char *ssid = "ESP32_Server";
const char *password = "server2018";
String htmlContent = " ";

AsyncWebServer server(80);

void handleRoot(AsyncWebServerRequest *request) {
  request->send(200, "text/html", "<html><head><title>ESP32 Server</title></head><body><h1>Hello from ESP32!</h1></body></html>");
}

void handleHTMLUpload(AsyncWebServerRequest *request) {
  htmlContent = "";

  if(request->hasArg("html") && request->hasArg("css")){
    String html = request->arg("html");
    String css = request->arg("css");
    htmlContent = "<!DOCTYPE html><html><head><style>" + css + "</style></head><body>" + html + "</body></html>";
    request->send(200, "text/html", htmlContent);
  }
  else {
    request->send(400, "text/plain", "Bad Request: Missing HTML or CSS parameters");
  }
}

void setup() {
  Serial.begin(115200);

  // Set up ESP32 as an Access Point (AP)
  WiFi.softAP(ssid, password);

  Serial.println("Access Point started");
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());

  server.on("/", HTTP_GET, handleRoot);
  server.on("/upload", HTTP_POST, handleHTMLUpload); // Use handleHTMLUpload as the handler

  server.begin();
}

void loop() {
  // Handle client requests
}
