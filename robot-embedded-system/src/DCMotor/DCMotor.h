#ifndef DCMOTOR_H
#define DCMOTOR_H

class DCMotor
{
public:
    DCMotor(int input0, int input1, int enable);
    void setMotorRotation(int rotation);
    void setMotorSpeed(int speed);

private:
	int input0;
    int input1;
    int enable;
};

#endif
