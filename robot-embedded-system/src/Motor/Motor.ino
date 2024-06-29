#include "Motor.hpp"

void setup()
{
    Motor motor(25, 26, 27);
    motor.setMotorData(CW, ZERO);
    motor.setMotorData(AntiCW, ONE);
    motor.setMotorData(Stop, TWO);
}

void loop() {}