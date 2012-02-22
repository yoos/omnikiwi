/*! \file telemetry.h
 *  \author Soo-Hyun Yoo
 *  \brief Some functions to make sending telemetry data simpler to code.
 *
 *  Details.
 */

#ifndef TELEMETRY_H
#define TELEMETRY_H

#include "globals.h"

void sendTelemetry(int nextRuntime) {
    // Send move number.
    sp(moveCounter);
    sp("  ");

    // ========================================================================
    // Report motor values.
    // ========================================================================
    #ifdef SEND_MOTOR_VALUES
    sp("M( ");
    for (int i=0; i<3; i++) {
        if (digOut[i]) {
            sp("+");
        }
        else {
            sp("-");
        }
        sp(analogOut[i]);
        sp(" ");
    }
    sp(")  ");
    #endif // SEND_MOTOR_VALUES

    // ========================================================================
    // Read LED distance sensors.
    // ========================================================================
    #ifdef SEND_SENSOR_READINGS
    sp("D( ");
    for (int i=0; i<6; i++) {
        sp(distSensors[i]);
        sp(" ");
    }
    sp(")  ");
    #endif // SEND_SENSOR_READINGS

    // Report loop time.
    sp("dt: ");
    spln((int) (micros() - (nextRuntime - MASTER_DT)));
}

#endif // TELEMETRY_H

