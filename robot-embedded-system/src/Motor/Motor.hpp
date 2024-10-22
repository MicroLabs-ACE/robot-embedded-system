#ifndef MOTOR_HPP
#define MOTOR_HPP

#include <Arduino.h>
#include <assert.h>

const int RANGE = 50;
const int MAX_LEVEL = 5;

enum MotorRotation
{
    CW,
    AntiCW,
    Stop,
};

class Motor
{
public:
    Motor(int input0, int input1, int enable);
    void setMotorData(MotorRotation rotation, int level);

private:
    int input0;
    int input1;
    int enable;
};

#endif // MOTOR_HPP
