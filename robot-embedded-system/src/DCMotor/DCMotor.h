#ifndef DCMOTOR_H
#define DCMOTOR_H

class DCMotor
{
public:
    DCMotor(int input0, int input1, int enable);

    int input0;
    int input1;
    int enable;

    int* getPins();

private:
    int pins[3];
};

#endif