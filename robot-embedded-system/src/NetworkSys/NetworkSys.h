
#pragma once

#include <Arduino.h>
#include <WiFi.h>

enum ENetworkState { UNINITIALIZED, INITIALIZED, CONNECTED, INTERNET_ACCESS };

/**
 * Network implementation
 * This class holds the connection details, handles connection
 * and disconnection implementation.
 * Periodic check to ensure access to the internet, etc
 * */
class NetworkSys {
private:
  /* data */
  const char *ssid, *password;

public:
  ENetworkState status;
  NetworkSys(const char *ssid, const char *password);
  ~NetworkSys(void);
  // Handles connecting the module to the provided wifi credentials
  ENetworkState connect();
  // overloading function for scenarios with new credentials
  ENetworkState connect(const char *ssid, const char *password);
  // functionalities to generate details of the network
  // char* getRemoteIP();
  // char* getLocalIP();
  // int getConnectionSpeed();
  // checking if we have access to the internet
  // ENetworkState checkInternetAccess();
};
