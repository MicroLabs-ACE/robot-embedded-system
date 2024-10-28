#include <cstring>
#include <string>
#include "src/Obstacle_Avoidance_System/Obstacle_Avoidance_System.hpp"
#include "src/Two_Wheeled_Motor_System/Two_Wheeled_Motor_System.hpp"
#include "src/WiFi_Communication_System/WiFi_Communication_System.hpp"

const int INTERVAL_MS = 1000;

TwoWheeledMotorSystem motorSystem(18, 19, 21, 25, 26, 27);
ObstacleAvoidanceSystem obsAvoidSystem(12, 13, 14, 32, 33, 34);
WiFiCommunicationSystem wifiCommSystem;
WiFiConnectionType connectionType = WiFiConnectionType::ACCESS_POINT;
const char *ssid = "ZeRobot";
const char *password = "robotics";

std::string command;

void setup() {
  Serial.begin(115200);
  motorSystem.power(true);
  wifiCommSystem.connectWiFi(connectionType, ssid, password);
  Serial.println("Initialised");
}

void loop() {
  command = wifiCommSystem.getLastReceivedData();
  Serial.print("Command: ");
  Serial.println(command.c_str());
  motorSystem.control(command, obsAvoidSystem.isWithinThreshold());
  delay(INTERVAL_MS);
}
