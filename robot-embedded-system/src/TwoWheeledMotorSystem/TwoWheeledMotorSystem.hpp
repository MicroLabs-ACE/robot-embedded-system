#ifndef TWOWHEELED_MOTOR_SYSTEM_HPP
#define TWOWHEELED_MOTOR_SYSTEM_HPP

#include "../Motor/Motor.hpp"

class TwoWheeledMotorSystem
{
public:
    TwoWheeledMotorSystem(int leftInput0, int leftInput1, int leftEnable, int rightInput0, int rightInput1, int rightEnable);
    void control(const char *);
    void setSpeedLevel(SpeedLevel level);

private:
    Motor leftMotor;
    Motor rightMotor;
    SpeedLevel level;
};

#endif // TWOWHEELED_MOTOR_SYSTEM_HPP
