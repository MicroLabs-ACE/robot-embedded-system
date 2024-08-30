#include <cstring>
#include <string>
#include "src/Obstacle_Avoidance_System/Obstacle_Avoidance_System.hpp"
#include "src/Two_Wheeled_Motor_System/Two_Wheeled_Motor_System.hpp"
#include "src/WiFi_Communication_System/WiFi_Communication_System.hpp"

TwoWheeledMotorSystem motorSystem(18, 19, 21, 25, 26, 27);
// ObstacleAvoidanceSystem obsAvoidSystem(18, 19, 21, 25, 26, 27);
// WiFiCommunicationSystem wifiCommSystem;
// WiFiConnectionType connectionType = WiFiConnectionType::ACCESS_POINT;
// const char *ssid = "Wall-E";
// const char *password = "robotics";

std::string command = "N-03";

void setup() {
  Serial.begin(115200);
  motorSystem.power(true);
  motorSystem.control(command);
}

void loop() {}
