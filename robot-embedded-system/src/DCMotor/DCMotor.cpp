#include <Arduino.h>

#include "DCMotor.h"

DCMotor::DCMotor(int input0, int input1, int enable) : input0(input0), input1(input1), enable(enable)
{
    pinMode(input0, OUTPUT);
    pinMode(input1, OUTPUT);
    pinMode(enable, OUTPUT);
}

int* DCMotor::getPins()
{
    pins[0] = input0;
    pins[1] = input1;
    pins[2] = enable;

    return pins;
}