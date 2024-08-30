#ifndef WIFI_ROUTER_HPP
#define WIFI_ROUTER_HPP

#include <ArduinoJson.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <WiFi.h>

struct Router
{
    const char *path;                 // The URL path for this route (e.g., "/", "/sample")
    WebRequestMethod method;          // The HTTP method for this route (e.g., HTTP_GET)
    ArRequestHandlerFunction handler; // Pointer to the function that handles this route
};

class WiFiRouter
{

public:
    Router getRouters();
    void runWebServer();

private:
    void handleRoot(AsyncWebServerRequest *request);
    void handleSample(AsyncWebServerRequest *request);
    void onWebSocketEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len);
}

#endif // WIFI_ROUTER_HPP