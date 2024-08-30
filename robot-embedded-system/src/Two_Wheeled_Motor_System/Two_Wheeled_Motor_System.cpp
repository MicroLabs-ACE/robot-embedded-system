#include "Two_Wheeled_Motor_System.hpp"

const std::unordered_map<std::string, std::string>
    TwoWheeledMotorSystem::directionMap = {
        {"NO", "North"},     {"SO", "South"},     {"OW", "West"},
        {"OE", "East"},      {"NW", "NorthWest"}, {"NE", "NorthEast"},
        {"SW", "SouthWest"}, {"SE", "SouthEast"}};

TwoWheeledMotorSystem::TwoWheeledMotorSystem(int leftInput0, int leftInput1,
                                             int leftEnable, int rightInput0,
                                             int rightInput1, int rightEnable)
    : leftMotor(leftInput0, leftInput1, leftEnable),
      rightMotor(rightInput0, rightInput1, rightEnable), level(THREE),
      isOn(false) {}

void TwoWheeledMotorSystem::control(const std::string &command) {
  if (!isOn) {
    Serial.println("Power Off");
    return;
  }

  std::string direction = extractDirectionFromCommand(command);
  int speed = extractSpeedFromCommand(command);
  setSpeedLevel(static_cast<SpeedLevel>(speed));
  
  Serial.println(speed);

  if (direction == "OO") { // Origin - No movement
    leftMotor.setMotorData(Stop, ZERO);
    rightMotor.setMotorData(Stop, ZERO);
    Serial.println("Origin");
  } else if (direction == "NO") { // North - Forward
    leftMotor.setMotorData(CW, level);
    rightMotor.setMotorData(CW, level);
    Serial.println("North");
  } else if (direction == "SO") { // South - Backward
    leftMotor.setMotorData(AntiCW, level);
    rightMotor.setMotorData(AntiCW, level);
    Serial.println("South");
  } else if (direction == "OW") { // West - Left - Zero Radius Turning
    leftMotor.setMotorData(AntiCW, level);
    rightMotor.setMotorData(CW, level);
    Serial.println("West");
  } else if (direction == "OE") { // East - Right - Zero Radius Turning
    leftMotor.setMotorData(CW, level);
    rightMotor.setMotorData(AntiCW, level);
    Serial.println("East");
  } else if (direction ==
             "NW") { // NorthWest - ForwardLeft - Curved Path Turning
    leftMotor.setMotorData(CW, static_cast<SpeedLevel>(level / 2));
    rightMotor.setMotorData(CW, level);
    Serial.println("NorthWest");
  } else if (direction ==
             "NE") { // NorthEast - ForwardRight - Curved Path Turning
    leftMotor.setMotorData(CW, level);
    rightMotor.setMotorData(CW, static_cast<SpeedLevel>(level / 2));
    Serial.println("NorthEast");
  } else if (direction ==
             "SW") { // SouthWest - BackwardLeft - Curved Path Turning
    leftMotor.setMotorData(AntiCW, static_cast<SpeedLevel>(level / 2));
    rightMotor.setMotorData(AntiCW, level);
    Serial.println("SouthWest");
  } else if (direction ==
             "SE") { // SouthEast - BackwardRight - Curved Path Turning
    leftMotor.setMotorData(AntiCW, level);
    rightMotor.setMotorData(AntiCW, static_cast<SpeedLevel>(level / 2));
    Serial.println("SouthEast");
  }
}

void TwoWheeledMotorSystem::power(bool state) {
  isOn = state;
  if (!isOn) {
    leftMotor.setMotorData(Stop, ZERO);
    rightMotor.setMotorData(Stop, ZERO);
  }
}

void TwoWheeledMotorSystem::setSpeedLevel(SpeedLevel level) {
  this->level = level;
}

int TwoWheeledMotorSystem::extractSpeedFromCommand(const std::string &command) {
  return command.back() - '0';
}

std::string
TwoWheeledMotorSystem::extractDirectionFromCommand(const std::string &command) {
  return command.substr(0, 2);
}
