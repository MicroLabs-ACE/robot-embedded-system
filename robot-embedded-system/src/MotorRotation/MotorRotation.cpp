#include <Arduino.h>
#include "MotorRotation.hpp"

DCMotor motorLeft;
DCMotor motorRight;

void setDCMotor(DCMotor &dcMotor, int input0, int input1, int enable) {
  dcMotor.input0 = input0;
  dcMotor.input1 = input1;
  dcMotor.enable = enable;

  pinMode(dcMotor.input0, OUTPUT);
  pinMode(dcMotor.input1, OUTPUT);
  pinMode(dcMotor.enable, OUTPUT);
}

void setMotorData(DCMotor &dcMotor, MotorRotation rotation, int speed) {
  switch (rotation) {
    case CW:
      digitalWrite(dcMotor.input0, HIGH);
      digitalWrite(dcMotor.input1, LOW);
      break;

    case AntiCW:
      digitalWrite(dcMotor.input0, LOW);
      digitalWrite(dcMotor.input1, HIGH);
      break;

    case Stop:
      digitalWrite(dcMotor.input0, LOW);
      digitalWrite(dcMotor.input1, LOW);
      break;

    default:
      break;
  }

  analogWrite(dcMotor.enable, speed);
}


void controlMotor(char direction[3]) {
  Serial.println(direction);
  if (strcmp(direction, "OO") == 0) {
    Serial.println("Origin");
    setMotorData(motorLeft, MotorRotation::Stop, 0);
    setMotorData(motorRight, MotorRotation::Stop, 0);
  } else if (strcmp(direction, "NO") == 0) {
    Serial.println("North");
    setMotorData(motorLeft, MotorRotation::CW, highSpeed);
    setMotorData(motorRight, MotorRotation::CW, highSpeed);
  } else if (strcmp(direction, "SO") == 0) {
    Serial.println("South");
    setMotorData(motorLeft, MotorRotation::AntiCW, highSpeed);
    setMotorData(motorRight, MotorRotation::AntiCW, highSpeed);
  } else if (strcmp(direction, "OW") == 0) {
    Serial.println("West");
      setMotorData(motorLeft, MotorRotation::AntiCW, highSpeed); // Spin the left motor backward
      setMotorData(motorRight,  MotorRotation::CW, highSpeed);    // Spin the right motor forward
  } else if (strcmp(direction, "OE") == 0) {
    Serial.println("East");
    setMotorData(motorLeft, MotorRotation::CW, highSpeed); // Spin the left motor forward
    setMotorData(motorRight, MotorRotation::AntiCW, highSpeed); // Spin the right motor backward
  } else if (strcmp(direction, "NE") == 0) {
    Serial.println("NorthEast");
    setMotorData(motorLeft, MotorRotation::CW, highSpeed);
    setMotorData(motorRight, MotorRotation::CW, lowSpeed);
  } else if (strcmp(direction, "NW") == 0) {
    Serial.println("NorthWest");
    setMotorData(motorLeft, MotorRotation::CW, lowSpeed);
    setMotorData(motorRight, MotorRotation::CW, highSpeed);
  } else if (strcmp(direction, "SE") == 0) {
    Serial.println("SouthEast");
    setMotorData(motorLeft, MotorRotation::AntiCW, highSpeed);
    setMotorData(motorRight, MotorRotation::AntiCW, lowSpeed);
  } else if (strcmp(direction, "SW") == 0) {
    Serial.println("SouthWest");
    setMotorData(motorLeft, MotorRotation::AntiCW, lowSpeed);
    setMotorData(motorRight, MotorRotation::AntiCW, highSpeed);
  }
}
