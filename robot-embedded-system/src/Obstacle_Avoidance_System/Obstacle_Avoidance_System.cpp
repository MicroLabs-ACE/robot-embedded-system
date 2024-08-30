#include "Obstacle_Avoidance_System.hpp"

ObstacleAvoidanceSystem::ObstacleAvoidanceSystem(
    int leftTrigPin, int leftEchoPin, int middleTrigPin, int middleEchoPin,
    int rightTrigPin, int rightEchoPin)
    : leftUSensor(leftTrigPin, leftEchoPin),
      middleUSensor(middleTrigPin, middleEchoPin),
      rightUSensor(rightTrigPin, rightEchoPin) {}

int ObstacleAvoidanceSystem::getDistance(const UltrasonicSensor &uSensor) {
  digitalWrite(uSensor.getTrigPin(), LOW);
  delayMicroseconds(RISE_TIME);
  digitalWrite(uSensor.getTrigPin(), HIGH);
  delayMicroseconds(FALL_TIME);
  digitalWrite(uSensor.getTrigPin(), LOW);

  long duration = pulseIn(uSensor.getEchoPin(), HIGH);
  int distance = duration * SPEED_OF_SOUND_MS / 2;
  return distance;
}

bool ObstacleAvoidanceSystem::isWithinThreshold() {
  int middleDistance = getDistance(middleUSensor);
  return middleDistance < THRESHOLD_CM;
}
