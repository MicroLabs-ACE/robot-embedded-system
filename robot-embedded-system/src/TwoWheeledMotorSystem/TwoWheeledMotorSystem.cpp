#include <cstring>
#include "TwoWheeledMotorSystem.hpp"

TwoWheeledMotorSystem::TwoWheeledMotorSystem(int leftInput0, int leftInput1, int leftEnable, int rightInput0, int rightInput1, int rightEnable)
    : leftMotor(leftInput0, leftInput1, leftEnable), rightMotor(rightInput0, rightInput1, rightEnable), level(THREE)
{
  setSpeedLevel(THREE);
}

void TwoWheeledMotorSystem::control(const char *direction)
{
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
}

void TwoWheeledMotorSystem::setSpeedLevel(SpeedLevel level)
{
  this->level = level;
}
