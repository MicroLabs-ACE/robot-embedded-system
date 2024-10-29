#ifndef OBSTACLE_AVOIDANCE_SYSTEM_HPP
#define OBSTACLE_AVOIDANCE_SYSTEM_HPP
#include "../Ultrasonic_Sensor/Ultrasonic_Sensor.hpp"
#include <Arduino.h>

class ObstacleAvoidanceSystem {
public:
  ObstacleAvoidanceSystem(int leftTrigPin, int leftEchoPin, int middleTrigPin,
                          int middleEchoPin, int rightTrigPin,
                          int rightEchoPin);
  bool isWithinThreshold();

private:
  static const int RISE_TIME = 10;
  static const int FALL_TIME = 2;
  static constexpr float SPEED_OF_SOUND_MS = 0.036;
  static const int THRESHOLD_CM = 5;

  UltrasonicSensor leftUSensor;
  UltrasonicSensor middleUSensor;
  UltrasonicSensor rightUSensor;

  int getDistance(const UltrasonicSensor &uSensor);
};

#endif // OBSTACLE_AVOIDANCE_SYSTEM_HPP
