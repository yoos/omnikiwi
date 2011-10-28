#ifndef FOOMOTOR_H
#define FOOMOTOR_H

class FooMotor
{
    int inputAPin;
    int inputBPin;
    int analogSig;

public:
    FooMotor (int, int);
    void Spin (int);
};

#endif // FOOMOTOR_H

