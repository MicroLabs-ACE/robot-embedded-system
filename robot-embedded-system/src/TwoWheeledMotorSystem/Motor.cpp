#include <Arduino.h>
#include "Motor.hpp"

Motor::Motor(int input0, int input1, int enable) : input0(input0), input1(input1), enable(enable)
{
	pinMode(input0, OUTPUT);
	pinMode(input1, OUTPUT);
	pinMode(enable, OUTPUT);
}

void Motor::setMotorData(MotorRotation rotation, SpeedLevel level)
{
	switch (rotation)
	{
	case MotorRotation::Stop:
		digitalWrite(input0, LOW);
		digitalWrite(input1, LOW);
		break;

	case MotorRotation::CW:
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

	analogWrite(enable, level);
}
