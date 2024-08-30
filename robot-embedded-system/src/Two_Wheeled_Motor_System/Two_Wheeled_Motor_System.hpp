#ifndef TWOWHEELED_MOTOR_SYSTEM_HPP
#define TWOWHEELED_MOTOR_SYSTEM_HPP

#include "../Motor/Motor.hpp"
#include <Arduino.h>
#include <unordered_map>
#include <string>

class TwoWheeledMotorSystem {
public:
  TwoWheeledMotorSystem(int leftInput0, int leftInput1, int leftEnable,
                        int rightInput0, int rightInput1, int rightEnable);
  void control(const char *direction);
  void setSpeedLevel(SpeedLevel level);
  void powerControl(bool state);

private:
  Motor leftMotor;
  Motor rightMotor;
  SpeedLevel level;
  bool isOn;
  void printDirection(const char *direction);
  static const std::unordered_map<std::string, std::string> directionMap;
};

#endif // TWOWHEELED_MOTOR_SYSTEM_HPP