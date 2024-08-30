#ifndef OBSTACLE_AVOIDANCE_SYSTEM_HPP
#define OBSTACLE_AVOIDANCE_SYSTEM_HPP

#include <Arduino.h>
#include "../Ultrasonic_Sensor/Ultrasonic_Sensor.hpp"

class ObstacleAvoidanceSystem
{
    const int RISE_TIME = 10;
    const int FALL_TIME = 2;
    const float SPEED_OF_SOUND_MS = 0.036;
    const int THRESHOLD_CM = 5;

public:
    bool isWithinThreshold();

private:
    UltrasonicSensor leftUSensor;
    UltrasonicSensor middleUSensor;
    UltrasonicSensor rightUSensor;

    int getDistance(UltrasonicSensor uSensor);
}

#endif // OBSTACLE_AVOIDANCE_SYSTEM_HPP