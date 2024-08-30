#include <cstring>
#include "Two_Wheeled_Motor_System.hpp"

TwoWheeledMotorSystem::TwoWheeledMotorSystem(int leftInput0, int leftInput1, int leftEnable, int rightInput0, int rightInput1, int rightEnable)
    : leftMotor(leftInput0, leftInput1, leftEnable), rightMotor(rightInput0, rightInput1, rightEnable), level(THREE)
{
  setSpeedLevel(THREE);
}

void TwoWheeledMotorSystem::control(const char *direction)
{

  if (!isOn) {
    Serial.println("System Off");
    return;
  }
  
  if (strcmp(direction, "OO") == 0) // Origin - No movement
  {
    this->leftMotor.setMotorData(Stop, ZERO);
    this->rightMotor.setMotorData(Stop, ZERO);
  }
  else if (strcmp(direction, "NO") == 0) // North - Forward
  {
    this->leftMotor.setMotorData(CW, level);
    this->rightMotor.setMotorData(CW, level);
  }
  else if (strcmp(direction, "SO") == 0) // South - Backward
  {
    this->leftMotor.setMotorData(AntiCW, level);
    this->rightMotor.setMotorData(AntiCW, level);
  }
  else if (strcmp(direction, "OW") == 0) // West - Left - Zero Radius Turning
  {
    this->leftMotor.setMotorData(AntiCW, level);
    this->rightMotor.setMotorData(CW, level);
  }
  else if (strcmp(direction, "OE") == 0) // East - Right - Zero Radius Turning
  {
    this->leftMotor.setMotorData(CW, level);
    this->rightMotor.setMotorData(AntiCW, level);
  }
  else if (strcmp(direction, "NW") == 0) // NorthWest - ForwardLeft - Curved Path Turning
  {
    this->leftMotor.setMotorData(Stop, ZERO);
    this->rightMotor.setMotorData(CW, level);
  }
  else if (strcmp(direction, "NE") == 0) // NorthEast - ForwardRight - Curved Path Turning
  {
    this->leftMotor.setMotorData(CW, level);
    this->rightMotor.setMotorData(Stop, ZERO);
  }
  else if (strcmp(direction, "SW") == 0) // SouthWest - BackwardLeft - Curved Path Turning
  {
    this->leftMotor.setMotorData(Stop, ZERO);
    this->rightMotor.setMotorData(AntiCW, level);
  }
  else if (strcmp(direction, "SE") == 0) // SouthEast - BackwardRight - Curved Path Turning
  {
    this->leftMotor.setMotorData(AntiCW, level);
    this->rightMotor.setMotorData(Stop, ZERO);
  }

  printDirection(direction)
}


void TwoWheeledMotorSystem::printDirection(const char *direction){
  static const std::unordered_map<std::string, std::string> directionMap = {
    {"OO", "Origin"},
    {"NO", "North"},
    {"SO", "South"},
    {"OW", "West"},
    {"OE", "East"},
    {"NW", "NorthWest"},
    {"NE", "NorthEast"},
    {"SW", "SouthWest"},
    {"SE", "SouthEast"}
  };

  auto it = directionMap.find(direction);
  if (it != directionMap.end()){
    Serial.println(it->second.c_str());
  } else {
    Serial.println("Invalid direction");
  }
}

void TwoWheeledMotorSystem::powerControl(bool state) {
  this->isOn = state;
  if (!isOn) {
    this->leftMotor.setMotorData(Stop, ZERO);
    this->rightMotor.setMotorData(Stop, ZERO);
  }
}

void TwoWheeledMotorSystem::setSpeedLevel(SpeedLevel level)
{
  this->level = level;
}
