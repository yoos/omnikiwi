/*! \file sensors.h
 *  \author Soo-Hyun Yoo
 *  \brief Sensor readings.
 */

#ifndef SENSORS_H
#define SENSORS_H

#include "globals.h"

#define SENSORS_LPF_DEPTH 5   // Enable low-pass filter.

class Sensors {
    #ifdef SENSORS_LPF_DEPTH
    int lpfIndex[NUM_OF_LEDS];
    float lpfVal[NUM_OF_LEDS][SENSORS_LPF_DEPTH];   // Low-pass filter values for each LED.
    #endif // SENSORS_LPF_DEPTH

public:
    Sensors();
    void chargeLED(int);
    void readLED(int);
    void read();
};

#endif // SENSORS_H

