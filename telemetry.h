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
    // ========================================================================
    // Report motor values.
    // ========================================================================
    #ifdef SEND_MOTOR_VALUES
    sp("MR: ");
    sp(pwmOut[0]);
    sp("  ");
    sp("ML: ");
    sp(pwmOut[1]);
    sp("  ");
    #endif // SEND_MOTOR_VALUES

    // Report loop time.
    sp("dt: ");
    spln((int) (micros() - (nextRuntime - MASTER_DT)));
}

#endif // TELEMETRY_H

