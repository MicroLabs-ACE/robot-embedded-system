const int RISE_TIME = 10;
const int FALL_TIME = 2;
const float SPEED_OF_SOUND_MS = 0.036;
const int THRESHOLD_CM = 5;

struct UltrasonicSensor {
  int trigPin;
  int echoPin;
};

UltrasonicSensor uSensorMiddle;
UltrasonicSensor uSensorLeft;
UltrasonicSensor uSensorRight;
int middleDistance;
int leftDistance;
int rightDistance;

void setup() {
  uSensorMiddle = initUltrasonicSensor(3, 5);
  uSensorLeft = initUltrasonicSensor(6, 9);              
  uSensorRight = initUltrasonicSensor(10, 11);
  Serial.begin(9600);
}

void loop() {
  middleDistance = getDistance(uSensorMiddle);
  leftDistance = getDistance(uSensorLeft);
  rightDistance = getDistance(uSensorRight);

  Serial.print("Middle: ");
  Serial.println(middleDistance);
  Serial.print("Left: ");
  Serial.println(leftDistance);
  Serial.print("Right: ");
  Serial.println(rightDistance);
  Serial.println();
  delay(1000);
  // if (isWithinThreshold(middleDistance)) {

  //   leftDistance = getDistance(uSensorLeft);
  //   rightDistance = getDistance(uSensorRight);

  //   if (leftDistance < rightDistance) {
  //     Serial.println(rightDistance);
  //   } else {
  //     Serial.println(leftDistance);
  //   }
  // }
}

int getDistance(UltrasonicSensor uSensor) {
  digitalWrite(uSensor.trigPin, LOW);
  delay(RISE_TIME);
  digitalWrite(uSensor.trigPin, HIGH);
  delay(FALL_TIME);
  digitalWrite(uSensor.trigPin, LOW);

  int duration = pulseIn(uSensor.echoPin, HIGH);
  int distance = duration * SPEED_OF_SOUND_MS / 2;

  return distance;
}
bool isWithinThreshold(int distance) {
  return distance < THRESHOLD_CM;
}


UltrasonicSensor initUltrasonicSensor(int trigPin, int echoPin) {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  UltrasonicSensor uSensor;
  uSensor.trigPin = trigPin;
  uSensor.echoPin = echoPin;

  return uSensor;
}