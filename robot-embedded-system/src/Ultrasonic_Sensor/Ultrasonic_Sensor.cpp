#include "Ultrasonic_Sensor.hpp"

UltrasonicSensor::UltrasonicSensor(int trigPin, int echoPin) : trigPin(trigPin), echoPin(echoPin)
{
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
}