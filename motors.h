/*! \file motors.h
 *  \author Soo-Hyun Yoo
 *  \brief Calculate PWM outputs for motors based on target rotation and translation.
 */

#ifndef MOTORS_H
#define MOTORS_H

#include "globals.h"

void calculate_pwm_outputs(float rot, float trans) {
    #ifdef REL_BODY

    // Calculate motor outputs to move relative to the body.

    #endif // REL_BODY


    #ifdef REL_WORLD

    // Calculate motor outputs to move relative to the world.

    #endif // REL_WORLD
}

#endif // MOTORS_H

