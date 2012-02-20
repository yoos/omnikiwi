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
uint16_t w2pwm(float rotSpeed) {
    int sign = (rotSpeed > 0) ? 1 : -1;
    return (uint16_t) (TMIN + (TMAX - TMIN) * sign * (rotSpeed / MAX_MOTOR_SPEED));
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
        pwmOut[i] = w2pwm(motorSpeed[i]);
    }

    #endif // MOVE_REL_BODY


    #ifdef MOVE_REL_WORLD

    // Calculate motor outputs to move relative to the world.

    #endif // MOVE_REL_WORLD
}

#endif // MOTORS_H

