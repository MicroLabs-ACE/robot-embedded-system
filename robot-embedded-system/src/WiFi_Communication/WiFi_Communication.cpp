#include "WiFiCommunication.hpp"

bool WiFiCommunication::setStaticIPAddress(IPAddress localIPAddress,
                                           IPAddress gateway,
                                           IPAddress subnet) {
  return WiFi.config(localIPAddress, gateway, subnet);
}

bool WiFiCommunication::wifiAsStation(const char *ssid, const char *password) {
  int numberOfRetries = 0;
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED && numberOfRetries < 200) {
    delay(1000);
    numberOfRetries++;
  }

  return WiFi.status() == WL_CONNECTED;
}

bool WiFiCommunication::wifiAsAccessPoint(const char *ssid,
                                          const char *password) {
  return WiFi.softAP(ssid, password);
}

bool WiFiCommunication::connectWiFi(WiFiConnectionType connectionType,
                                    const char *ssid, const char *password) {
  bool result = false;

  switch (connectionType) {
  case STATION: {
    IPAddress localIPAddress(192, 168, 1, 184);
    IPAddress gateway(192, 168, 1, 1);
    IPAddress subnet(255, 255, 0, 0);

    bool isStaticIPAddress =
        WiFiCommunication::setStaticIPAddress(localIPAddress, gateway, subnet);
    if (!isStaticIPAddress) {
      return false;
    }

    result = WiFiCommunication::wifiAsStation(ssid, password);
  } break;

  case ACCESS_POINT:
    result = WiFiCommunication::wifiAsAccessPoint(ssid, password);
    break;

  default:
    break;
  }

  if (result) {
    router.runWebServer();
  }

  return result;
}
