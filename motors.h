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
    return (uint16_t) (TMIN + (TMAX - TMIN) * (rotSpeed / MAX_MOTOR_SPEED));
}

/*! Convert linear velocity (m/s) to required wheel rotation speed (rad/s).
 */
float v2w(float velocity) {
    return velocity / (WHEEL_DIAMETER * PI) * 2*PI;
}

/*! Calculate PWM outputs for an input rotation speed (rad/s) and translation direction (rad) at some speed (m/s).
 *
 *  \param rotSpeed Rotation speed in radians/s
 *  \param transDir Translation direction in radians
 *  \param transSpeed Translation speed in m/s
 */
void calculate_pwm_outputs(float rotSpeed, float transDir, float transSpeed) {
    float transComponent[3];   // Component of motor spin for translation.

    #ifdef MOVE_REL_BODY
    // Calculate motor outputs to move relative to the body.

    transComponent[MOTOR_T] = v2w(transSpeed * sin(transDir));
    transComponent[MOTOR_R] = v2w(transSpeed * sin(transDir - PI/3));
    transComponent[MOTOR_L] = v2w(transSpeed * sin(transDir - 2*PI/3));

    for (int i=0; i<3; i++) {
        pwmOut[i] = w2pwm(rotSpeed) + w2pwm(transComponent[i]);
    }

    #endif // MOVE_REL_BODY


    #ifdef MOVE_REL_WORLD

    // Calculate motor outputs to move relative to the world.

    #endif // MOVE_REL_WORLD
}

#endif // MOTORS_H

