#include <Arduino.h>

#include "DCMotor.h"

DCMotor::DCMotor(int input0, int input1, int enable) : input0(input0), input1(input1), enable(enable)
{
    pinMode(input0, OUTPUT);
    pinMode(input1, OUTPUT);
    pinMode(enable, OUTPUT);
}

void DCMotor::setMotorRotation(int rotation) 
{
	switch(rotation) 
	{
		case 0: // Stop
			digitalWrite(input0, LOW);
			digitalWrite(input1, LOW);
			break;
			
		case 1: // Clockwise
			digitalWrite(input0, HIGH);
			digitalWrite(input1, LOW);
			break;
			
		case -1: // Anti-Clockwise
			digitalWrite(input0, LOW);
			digitalWrite(input1, HIGH);
			break;
			
		default:
			break;
		
	}
}

void DCMotor::setMotorSpeed(int speed) 
{
	analogWrite(enable, speed);
}
