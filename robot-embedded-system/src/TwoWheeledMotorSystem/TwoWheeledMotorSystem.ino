#include "TwoWheeledMotorSystem.hpp"

void setup()
{
    TwoWheeledMotorSystem motorSystem(18, 19, 21, 25, 26, 27);
    motorSystem.control("OO");
    motorSystem.control("NO");
    motorSystem.control("SO");
    motorSystem.control("OW");
    motorSystem.control("OE");
}

void loop() {}
