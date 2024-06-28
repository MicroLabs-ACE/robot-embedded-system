#include "Network.h"

const char *ssid = "pan";
const char *password = "passwordx";

Network networkManager = Network(ssid, password);

void setup()
{
    Serial.begin(9600);
    networkManager.connect();
}

void loop() {}
