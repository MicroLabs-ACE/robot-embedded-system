struct DCMotor
{
  int input0;
  int input1;
  int enable;
};

enum MotorRotation
{
  CW,
  AntiCW,
  Stop,
};

enum MotorDirection
{
  FORWARD,
  BACKWARD,
  LEFT,
  RIGHT,
};

void setDCMotor(DCMotor &dcMotor, int input0, int input1, int enable)
{
  dcMotor.input0 = input0;
  dcMotor.input1 = input1;
  dcMotor.enable = enable;

  pinMode(dcMotor.input0, OUTPUT);
  pinMode(dcMotor.input1, OUTPUT);
  pinMode(dcMotor.enable, OUTPUT);
}

void setMotorData(DCMotor &dcMotor, MotorRotation rotation, int speed)
{
  switch (rotation)
  {
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

void move(DCMotor &motorLeft, DCMotor &motorRight, MotorRotation rotation, MotorDirection direction, int speed)
{
  switch (direction)
  {
  case FORWARD:
    setMotorData(motorLeft, CW, speed);
    setMotorData(motorRight, CW, speed);
    break;

  case BACKWARD:
    setMotorData(motorLeft, AntiCW, speed);
    setMotorData(motorRight, AntiCW, speed);
    break;

  case LEFT:
    setMotorData(motorLeft, AntiCW, speed); // Spin the left motor backward
    setMotorData(motorRight, CW, speed);    // Spin the right motor forward
    break;

  case RIGHT:
    setMotorData(motorLeft, CW, speed);      // Spin the left motor forward
    setMotorData(motorRight, AntiCW, speed); // Spin the right motor backward
    break;

  default:
    break;
  }
}

void stopMotors(DCMotor &motorLeft, DCMotor &motorRight)
{
  setMotorData(motorLeft, Stop, 0);  // Stop left motor
  setMotorData(motorRight, Stop, 0); // Stop right motor
}

void setup()
{
  DCMotor motorLeft;
  DCMotor motorRight;

  setDCMotor(motorLeft, 11, 10, 9);
  setDCMotor(motorRight, 5, 6, 3);

  MotorRotation rotation = CW;
  MotorDirection rightDirection = RIGHT;
  MotorDirection leftDirection = LEFT;
  MotorDirection forwardDirection = FORWARD;
  MotorDirection backwardDirection = BACKWARD;

  int speed = 157;

  move(motorLeft, motorRight, rotation, forwardDirection, speed);
  delay(1000);

  move(motorLeft, motorRight, rotation, backwardDirection, speed);
  delay(2000);

  move(motorLeft, motorRight, rotation, rightDirection, speed);
  delay(2000);

  move(motorLeft, motorRight, rotation, leftDirection, speed);
  delay(1000);

  stopMotors(motorLeft, motorRight);
}

void loop()
{
}