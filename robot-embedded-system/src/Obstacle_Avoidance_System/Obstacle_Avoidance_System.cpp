#include "Obstacle_Avoidance_System.hpp"

ObstacleAvoidanceSystem::ObstacleAvoidanceSystem(int leftTrigPin, int leftEchoPin, int middleTrigPin, int middleEchoPin, int rightTrigPin, int rightEchoPin) : leftUSensor(leftTrigPin, leftEchoPin), middleUSensor(middleTrigPin, middleEchoPin), rightUSensor(rightTrigPin, rightEchoPin) {}

int ObstacleAvoidanceSystem::getDistance(UltrasonicSensor uSensor)
{
    digitalWrite(uSensor.trigPin, LOW);
    delay(ObstacleAvoidanceSystem::RISE_TIME);
    digitalWrite(uSensor.trigPin, HIGH);
    delay(ObstacleAvoidanceSystem::FALL_TIME);
    digitalWrite(uSensor.trigPin, LOW);

    int duration = pulseIn(uSensor.echoPin, HIGH);
    int distance = duration * ObstacleAvoidanceSystem::SPEED_OF_SOUND_MS / 2;

    return distance;
}

bool ObstacleAvoidanceSystem::isWithinThreshold()
{
    int middleDistance = ObstacleAvoidanceSystem::getDistance(ObstacleAvoidanceSystem::middleUSensor);
    return middleDistance < ObstacleAvoidanceSystem::THRESHOLD_CM;
}

