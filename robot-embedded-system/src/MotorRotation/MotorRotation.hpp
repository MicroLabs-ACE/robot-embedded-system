#include "../DCMotor/DCMotor.h"
#ifndef __MOTOR_ROT__
#define __MOTOR_ROT__

int highSpeed = 153;
int lowSpeed = 77;
int speedLevel = 3;

DCMotor motorLeft;
DCMotor motorRight;

enum MotorRotation {
  CW,
  AntiCW,
  Stop,
};



void setDCMotor(DCMotor &dcMotor, int input0, int input1, int enable);

void setMotorData(DCMotor &dcMotor, MotorRotation rotation, int speed);

void controlMotor(char direction[3]);

#endif