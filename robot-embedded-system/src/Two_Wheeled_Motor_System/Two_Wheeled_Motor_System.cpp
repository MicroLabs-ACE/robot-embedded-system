#include "Two_Wheeled_Motor_System.hpp"

const std::unordered_map<std::string, std::string>
    TwoWheeledMotorSystem::directionMap = {
        {"OO", "Origin"},    {"NO", "North"},     {"SO", "South"},
        {"OW", "West"},      {"OE", "East"},      {"NW", "NorthWest"},
        {"NE", "NorthEast"}, {"SW", "SouthWest"}, {"SE", "SouthEast"}};

TwoWheeledMotorSystem::TwoWheeledMotorSystem(int leftInput0, int leftInput1,
                                             int leftEnable, int rightInput0,
                                             int rightInput1, int rightEnable)
    : leftMotor(leftInput0, leftInput1, leftEnable),
      rightMotor(rightInput0, rightInput1, rightEnable), level(THREE),
      isOn(false) {
  setSpeedLevel(THREE);
}

void TwoWheeledMotorSystem::control(const char *direction) {
  if (!isOn) {
    Serial.println("System Off");
    return;
  }

  std::string dir(direction);

  if (dir == "OO") { // Origin - No movement
    leftMotor.setMotorData(Stop, ZERO);
    rightMotor.setMotorData(Stop, ZERO);
  } else if (dir == "NO") { // North - Forward
    leftMotor.setMotorData(CW, level);
    rightMotor.setMotorData(CW, level);
  } else if (dir == "SO") { // South - Backward
    leftMotor.setMotorData(AntiCW, level);
    rightMotor.setMotorData(AntiCW, level);
  } else if (dir == "OW") { // West - Left - Zero Radius Turning
    leftMotor.setMotorData(AntiCW, level);
    rightMotor.setMotorData(CW, level);
  } else if (dir == "OE") { // East - Right - Zero Radius Turning
    leftMotor.setMotorData(CW, level);
    rightMotor.setMotorData(AntiCW, level);
  } else if (dir == "NW") { // NorthWest - ForwardLeft - Curved Path Turning
    leftMotor.setMotorData(CW, static_cast<SpeedLevel>(level / 2));
    rightMotor.setMotorData(CW, level);
  } else if (dir == "NE") { // NorthEast - ForwardRight - Curved Path Turning
    leftMotor.setMotorData(CW, level);
    rightMotor.setMotorData(CW, static_cast<SpeedLevel>(level / 2));
  } else if (dir == "SW") { // SouthWest - BackwardLeft - Curved Path Turning
    leftMotor.setMotorData(AntiCW, static_cast<SpeedLevel>(level / 2));
    rightMotor.setMotorData(AntiCW, level);
  } else if (dir == "SE") { // SouthEast - BackwardRight - Curved Path Turning
    leftMotor.setMotorData(AntiCW, level);
    rightMotor.setMotorData(AntiCW, static_cast<SpeedLevel>(level / 2));
  }

  printDirection(direction);
}

void TwoWheeledMotorSystem::printDirection(const char *direction) {
  auto it = directionMap.find(direction);
  if (it != directionMap.end()) {
    Serial.println(it->second.c_str());
  } else {
    Serial.println("Invalid direction");
  }
}

void TwoWheeledMotorSystem::powerControl(bool state) {
  isOn = state;
  if (!isOn) {
    leftMotor.setMotorData(Stop, ZERO);
    rightMotor.setMotorData(Stop, ZERO);
  }
}

void TwoWheeledMotorSystem::setSpeedLevel(SpeedLevel level) {
  this->level = level;
}
