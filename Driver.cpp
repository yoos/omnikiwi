#include "Driver.h"
#include <math.h>

Driver::Driver(FooMotor& a, FooMotor& b, FooMotor& c) {
   motorA = a;
   motorB = b;
   motorC = c;

}

Driver::Drive(float dir, float rot) {
    float vx = cos(dir);
    float vy = sin(dir);

    aSpeed = (2*vx + rot)/3;
    bSpeed = (-vx - sqrt(3)*vy + rot)/3;
    cSpeed = (-vx + sqrt(3)*vy + rot)/3;

    motorA.Spin(aSpeed);
    motorB.Spin(bSpeed);
    motorC.Spin(cSpeed);
}
