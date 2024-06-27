#include <Arduino.h>

#include "Motor.h"


Motor::Motor(int input0, int input1, int enable) : input0(input0), input1(input1), enable(enable)
{
    pinMode(input0, OUTPUT);
    pinMode(input1, OUTPUT);
    pinMode(enable, OUTPUT);
}

void Motor::setMotorRotation(MotorRotation rotation) 
{
	switch(rotation) 
	{
		case MotorRotation::Stop:
			digitalWrite(input0, LOW);
			digitalWrite(input1, LOW);
			break;
			
		case MotorRotation::CW: // Clockwise
			digitalWrite(input0, HIGH);
			digitalWrite(input1, LOW);
			break;
			
		case MotorRotation::AntiCW:
			digitalWrite(input0, LOW);
			digitalWrite(input1, HIGH);
			break;
			
		default:
			break;
		
	}
}



void Motor::setMotorSpeed(int speed) 
{
	analogWrite(enable, speed);
}
