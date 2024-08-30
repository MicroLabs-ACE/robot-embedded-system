#include <WiFi_Routes.hpp>

void WiFiRouter::handleRoot(AsyncWebServerRequest *request)
{
    IPAddress remoteIP = request->client()->remoteIP();
    DynamicJsonDocument responseJSON(1024);
    responseJSON["message"] = "Hello, world.";
    responseJSON["data"] = remoteIP.toString();

    String responseString;
    serializeJson(responseJSON, responseString);
    request->send(200, "application/json", responseString);
}

void WiFiRouter::handleSample(AsyncWebServerRequest *request)
{
    request->send(200, "text/plain", "This is a sample route");
}

void WiFiRouter::onWebSocketEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len)
{
    switch (type)
    {
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

void WiFiRouter::runWebServer()
{
    static AsyncWebServer webserver(80);
    static AsyncWebSocket websocket("/ws");
    websocket.onEvent(WiFiRouter::onWebSocketEvent);
    webserver.addHandler(&websocket);

    // Struct to hold all information needed to define a route
    struct RouteDefinition
    {
        const char *path;                 // The URL path for this route (e.g., "/", "/sample")
        WebRequestMethod method;          // The HTTP method for this route (e.g., HTTP_GET)
        ArRequestHandlerFunction handler; // Pointer to the function that handles this route
    };

    // Array of route definitions
    // Each entry defines a route with its path, HTTP method, and handler function
    RouteDefinition routes[] = {
        {"/", HTTP_GET, WiFiRouter::handleRoot},
        {"/sample", HTTP_GET, WiFiRouter::handleSample},
    };

    // Loop through the array of route definitions
    // For each route, call webserver.on() to register the route with the server
    for (const auto &route : routes)
    {
        webserver.on(route.path, route.method, route.handler);
    }

    webserver.begin();
}