#ifndef DRIVER_H
#define DRIVER_H

#include "FooMotor.h"

class Driver {
public:
    FooMotor motorA;
    FooMotor motorB;
    FooMotor motorC;
    float aSpeed, bSpeed, cSpeed;

    Driver(FooMotor&, FooMotor&, FooMotor&);
    void Drive(float, float);
}

#endif // DRIVER_H

