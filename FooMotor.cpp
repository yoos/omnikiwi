#include "FooMotor.h"

FooMotor::FooMotor (int pin1, int pin2)
{
    inputAPin = pin1;
    inputBPin = pin2;
    pinMode(inputAPin, OUTPUT);
    pinMode(inputBPin, OUTPUT);
}

void FooMotor::Spin (int targetSpeed)
{
    targetSpeed = (targetSpeed+1) * 127.5
    if (targetSpeed > 128)
    {
        analogSig = (targetSpeed - 128)*2;
        analogWrite(inputAPin, analogSig);
        digitalWrite(inputBPin, LOW);
    }
    else if (targetSpeed < 128)
    {
        analogSig = targetSpeed*2;
        analogWrite(inputAPin, analogSig);
        digitalWrite(inputBPin, HIGH);
    }
    else
    {
        digitalWrite(inputAPin, LOW);
        digitalWrite(inputBPin, LOW);
    }
}

