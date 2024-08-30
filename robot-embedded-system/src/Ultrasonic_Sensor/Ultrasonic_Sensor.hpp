#ifndef ULTRASONIC_SENSOR_HPP
#define ULTRASONIC_SENSOR_HPP

#include <Arduino.h>

class UltrasonicSensor
{
public:
    UltrasonicSensor(int trigPin, int echoPin);

private:
    int trigPin;
    int echoPin;
}

#endif // ULTRASONIC_SENSOR_HPP