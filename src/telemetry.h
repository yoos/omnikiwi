/*! \file telemetry.h
 *  \author Soo-Hyun Yoo
 *  \brief Some functions to make sending telemetry data simpler to code.
 *
 *  Details.
 */

#ifndef TELEMETRY_H
#define TELEMETRY_H

#include "globals.h"

void sendTelemetry(uint64_t nextRuntime) {
    // Send move number.
    #ifdef SEND_MOVE_COUNTER
    sw(moveCounter);
    sw(FIELD_SER_TAG); sw(FIELD_SER_TAG);
    #endif // SEND_MOVE_COUNTER

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
    sw(FIELD_SER_TAG); sw(FIELD_SER_TAG);
    #endif // SEND_MOTOR_VALUES

    // ========================================================================
    // Read LED distance sensors.
    // ========================================================================
    #ifdef SEND_SENSOR_READINGS
    sw(SEN_SER_TAG);
    for (int i=0; i<NUM_OF_LEDS; i++) {
        sw((ledFiltered[i]+1)*250.0/1024.0);
    }
    sw(FIELD_SER_TAG); sw(FIELD_SER_TAG);
    #endif // SEND_SENSOR_READINGS

    // ========================================================================
    // Send direction?
    // ========================================================================
    #ifdef SEND_DIR
    sp("Dir( ");
    for (int i=0; i<NUM_OF_LEDS; i++) {
        if (ledFiltered[i] > MAZE_THRESHOLD_6CM) {
            sp("1");
        }
        else {
            sp("0");
        }
    }
    sp(" )  ");
    sw(FIELD_SER_TAG); sw(FIELD_SER_TAG);
    #endif // SEND_DIR

    // Report loop time.
    sp((float) (micros() - (nextRuntime - MASTER_DT))/1000);

    sw(0xde); sw(0xad); sw(0xbe); sw(0xef);
}

#endif // TELEMETRY_H

