#ifndef TWO_WHEELED_MOTOR_SYSTEM_HPP
#define TWO_WHEELED_MOTOR_SYSTEM_HPP

#include "../Motor/Motor.hpp"
#include <Arduino.h>
#include <string>
#include <unordered_map>

class TwoWheeledMotorSystem {
public:
  TwoWheeledMotorSystem(int leftInput0, int leftInput1, int leftEnable,
                        int rightInput0, int rightInput1, int rightEnable);
  void control(const std::string &command, bool isObstacleWithinThreshold);
  void power(bool state);

private:
  std::string extractDirectionFromCommand(const std::string &command);
  int extractSpeedFromCommand(const std::string &command);

  Motor leftMotor;
  Motor rightMotor;
  bool isOn;
  static const std::unordered_map<std::string, std::string> directionMap;
};

#endif // TWO_WHEELED_MOTOR_SYSTEM_HPP
