/*! \file motors.h
 *  \author Soo-Hyun Yoo
 *  \brief Calculate PWM outputs for motors based on target rotation and translation.
 */

#ifndef MOTORS_H
#define MOTORS_H

#include "globals.h"
#include <math.h>

/*! Convert wheel rotation speed (rad/s) to PWM.
 */
float w2analog(float rotSpeed) {
    int sign = (rotSpeed > 0) ? 1 : -1;
    if (rotSpeed >= 0) {
        return (TMAX - (TMAX - TMIN) * ( rotSpeed / MAX_MOTOR_SPEED));
    }
    else {
        return (TMIN + (TMAX - TMIN) * (-rotSpeed / MAX_MOTOR_SPEED));
    }
}

/*! Convert linear velocity (m/s) to required wheel rotation speed (rad/s).
 */
float v2w(float velocity) {
    return velocity / WHEEL_RADIUS;
}

/*! Calculate PWM outputs for an input rotation speed (rad/s) and translation direction (rad) at some speed (m/s).
 *
 *  \param rotSpeed Rotation speed in radians/s
 *  \param transDir Translation direction in radians
 *  \param transSpeed Translation speed in m/s
 */
void calculate_pwm_outputs(float rotSpeed, float transDir, float transSpeed) {
    float rotComponent;   // Rotational component of motor spin.
    float motorSpeed[3];

    #ifdef MOVE_REL_BODY
    // Calculate motor outputs to move relative to the body.

    rotComponent = rotSpeed * ROBOT_RADIUS / WHEEL_RADIUS;

    motorSpeed[MOTOR_T] = rotComponent + v2w(transSpeed * cos(transDir));
    motorSpeed[MOTOR_R] = rotComponent + v2w(transSpeed * cos(transDir - 2*PI/3));
    motorSpeed[MOTOR_L] = rotComponent + v2w(transSpeed * cos(transDir + 2*PI/3));

    sp("MS( ");
    for (int i=0; i<3; i++) {
        sp(motorSpeed[i]);
        sp(" ");
    }
    sp(")  ");

    for (int i=0; i<3; i++) {
        // Set direction of motors.
        digOut[i] = (motorSpeed[i] > 0) ? 1 : 0;   // TODO: Check this!

        // Set speed of motors.
        analogOut[i] = w2analog(motorSpeed[i]);
    }

    #endif // MOVE_REL_BODY


    #ifdef MOVE_REL_WORLD

    // Calculate motor outputs to move relative to the world.

    #endif // MOVE_REL_WORLD

    // ====================================================================
    // After finding the maximum and minimum motor values, limit, but NOT
    // fit, motor values to minimum and maximum throttle [TMIN, TMAX]).
    // Doing this incorrectly will result in motor values seemingly stuck
    // mostly at either extremes.
    // ====================================================================
    int mapUpper = analogOut[MOTOR_T] > analogOut[MOTOR_R] ? analogOut[MOTOR_T] : analogOut[MOTOR_R];
    mapUpper = mapUpper > analogOut[MOTOR_L] ? mapUpper : analogOut[MOTOR_L];
    mapUpper = mapUpper > TMAX ? mapUpper : TMAX;

    int mapLower = analogOut[MOTOR_T] < analogOut[MOTOR_R] ? analogOut[MOTOR_T] : analogOut[MOTOR_R];
    mapLower = mapLower < analogOut[MOTOR_L] ? mapLower : analogOut[MOTOR_L];
    mapLower = mapLower < TMIN ? mapLower : TMIN;

    // We shouldn't have to use these, but uncomment the following two
    // lines if analogOut goes crazy and makes mapUpper lower than mapLower:
    //mapUpper = mapUpper > TMIN ? mapUpper : TMIN+1;
    //mapLower = mapLower < TMAX ? mapLower : TMAX-1;

    // ====================================================================
    // If map bounds are reasonable, remap range to [mapLower, mapUpper].
    // Otherwise, kill motors. Note that map(), an Arduino function, does
    // integer math and truncates fractions.
    //
    // TODO: analogOut (and other quantities the Pilot calculates) should be
    // an integer representing the number of milliseconds of PWM duty
    // cycle.
    // ====================================================================
    for (int i=0; i<3; i++) {
        if (mapUpper > mapLower) {
            analogOut[i] = map(analogOut[i], mapLower, mapUpper, TMIN, TMAX);
        }
        else {
            analogOut[i] = TMIN;
        }
    }
}

#endif // MOTORS_H

