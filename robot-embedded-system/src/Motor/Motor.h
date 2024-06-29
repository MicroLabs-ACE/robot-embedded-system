#ifndef MOTOR_H
#define MOTOR_H


enum MotorRotation {
  CW,
  AntiCW,
  Stop,
};

class Motor
{
public:
    Motor(int input0, int input1, int enable);
    void setMotorRotation(MotorRotation rotation);
    void setMotorSpeed(int speed);

private:
	int input0;
    int input1;
    int enable;
};

#endif
