#include "WiFi_Communication_System.hpp"

std::string WiFiCommunicationSystem::lastReceivedData = "";

bool WiFiCommunicationSystem::setStaticIPAddress(IPAddress localIPAddress,
                                                 IPAddress gateway,
                                                 IPAddress subnet)
{
  return WiFi.config(localIPAddress, gateway, subnet);
}

bool WiFiCommunicationSystem::wifiAsStation(const char *ssid,
                                            const char *password)
{
  int numberOfRetries = 0;
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED && numberOfRetries < 200)
  {
    delay(1000);
    numberOfRetries++;
  }
  return WiFi.status() == WL_CONNECTED;
}

bool WiFiCommunicationSystem::wifiAsAccessPoint(const char *ssid,
                                                const char *password)
{
  return WiFi.softAP(ssid, password);
}

void WiFiCommunicationSystem::handleRoot(AsyncWebServerRequest *request)
{
  IPAddress remoteIP = request->client()->remoteIP();
  DynamicJsonDocument responseJSON(1024);
  responseJSON["message"] = "Hello, world.";
  responseJSON["data"] = remoteIP.toString();
  String responseString;
  serializeJson(responseJSON, responseString);
  request->send(200, "application/json", responseString);
  request->addHeader("Access-Control-Allow-Origin", "*");
  request->addHeader("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
  request->addHeader("Access-Control-Allow-Headers", "Content-Type, Authorization");

  void WiFiCommunicationSystem::handleCommand(AsyncWebServerRequest * request)
  {
    String command = request->arg("command");
    Serial.println("Received command: " + command);
    lastReceivedData = command.c_str();
    request->send(200, "text/plain", "Received command");
    request->addHeader("Access-Control-Allow-Origin", "*");
    request->addHeader("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
    request->addHeader("Access-Control-Allow-Headers", "Content-Type, Authorization");
  }

  std::string WiFiCommunicationSystem::getLastReceivedData()
  {
    return lastReceivedData;
  }

  void WiFiCommunicationSystem::runWebServer()
  {
    static AsyncWebServer webserver(80);

    Route routes[] = {{"/", HTTP_GET, handleRoot},
                      {"/", HTTP_POST, handleCommand}};

    for (const auto &route : routes)
    {
      webserver.on(route.path, route.method, route.handler);
    }

    webserver.begin();
  }

  bool WiFiCommunicationSystem::connectWiFi(WiFiConnectionType connectionType,
                                            const char *ssid,
                                            const char *password)
  {
    bool result = false;
    switch (connectionType)
    {
    case STATION:
    {
      IPAddress localIPAddress(192, 168, 1, 184);
      IPAddress gateway(192, 168, 1, 1);
      IPAddress subnet(255, 255, 0, 0);
      bool isStaticIPAddress =
          setStaticIPAddress(localIPAddress, gateway, subnet);
      if (!isStaticIPAddress)
      {
        return false;
      }
      result = wifiAsStation(ssid, password);
    }
    break;
    case ACCESS_POINT:
      result = wifiAsAccessPoint(ssid, password);
      break;
    default:
      break;
    }
    if (result)
    {
      runWebServer();
    }
    return result;
  }
