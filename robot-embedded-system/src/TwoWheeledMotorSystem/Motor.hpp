#ifndef MOTOR_HPP
#define MOTOR_HPP

enum MotorRotation
{
    CW,
    AntiCW,
    Stop,
};

enum SpeedLevel
{
    ZERO = 0,
    ONE = 51,
    TWO = 102,
    THREE = 153,
    FOUR = 204,
    FIVE = 255
};

class Motor
{
public:
    Motor(int input0, int input1, int enable);
    void setMotorData(MotorRotation rotation, SpeedLevel level);

private:
    int input0;
    int input1;
    int enable;
};

#endif // MOTOR_HPP
