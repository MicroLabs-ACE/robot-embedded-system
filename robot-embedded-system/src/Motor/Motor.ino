#include "Motor.h"

Motor dcMotor(25, 26, 27);

void setup()
{
    Serial.begin(9600);

    int *pins = dcMotor.getPins();
    Serial.print("Input 0: ");
    Serial.println(pins[0]);
    Serial.print("Input 1: ");
    Serial.println(pins[1]);
    Serial.print("Enable: ");
    Serial.println(pins[2]);
}

void loop() {}