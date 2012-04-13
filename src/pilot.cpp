/*! \file pilot.cpp
 *  \author Soo-Hyun Yoo
 *  \brief Source for Pilot class.
 *
 *  Details.
 */

#include "pilot.h"

Pilot::Pilot() {
    //Serial.begin(BAUDRATE);
    hasFood = false;
    okayToFly = false;

    // Assume serial inputs, all axes zeroed.
    serInput[SX] = 125;
    serInput[SY] = 125;
    serInput[ST] = 125;
    /* Keep Z value at some non-zero value (albeit very low so the tricopter 
     * doesn't fly off if something goes awry) so user is forced to adjust 
     * throttle before motors arm. */
    serInput[SZ] = 3;

    // Initialize trim to 0.
    throttleTrim = 0;

    //PID[PID_ROT_X].P = PID[PID_ROT_Y].P = XY_P_GAIN;
    //PID[PID_ROT_X].I = PID[PID_ROT_Y].I = XY_I_GAIN;
    //PID[PID_ROT_X].D = PID[PID_ROT_Y].D = XY_D_GAIN;

    //PID[PID_ROT_Z].P = Z_P_GAIN;
    //PID[PID_ROT_Z].I = Z_I_GAIN;
    //PID[PID_ROT_Z].D = Z_D_GAIN;

    numGoodComm = 0;   // Number of good communication packets.
    numBadComm = 0;   // Number of bad communication packets.

    // Set targetHeading to current heading. Initialize IMU first!
    targetHeading = heading;
}

void Pilot::listen() {
    if (Serial.available()) {
        serRead = Serial.read();

        if (serRead == SERHEAD) {   // Receive header.
            hasFood = true;   // Prepare food for watchdog.
            for (int i=0; i<PACKETSIZE; i++) {
                serRead = Serial.read();

                if (serRead >= INPUT_MIN && serRead <= INPUT_MAX) {
                    serInput[i] = serRead;
                    okayToFly = true;
                    numGoodComm++;
                }
                else {
                    i = 10;
                    okayToFly = false;
                    numBadComm++;
                    // Flush remaining buffer to avoid taking in the wrong values.
                    Serial.flush();
                }
            }
        }
        else {
            okayToFly = false;
        }
    }
}

void Pilot::fly() {
    //sp("(");
    //sp(numGoodComm);
    //sp("/");
    //sp(numBadComm);
    //sp(") ");

    if (okayToFly) {
        // Process inputs.
        update_joystick_input();
        process_joystick_buttons();

        // Calculate target values.
        targetHeading += joy.axes[ST]/125 * 1.5 / (MASTER_DT * CONTROL_LOOP_INTERVAL);   // Change target heading by a maximum of 1.5 rad/s.

        // Keep targetHeading within [-PI, PI].
        if (targetHeading > PI) {
            targetHeading -= 2*PI;
        }
        else if (targetHeading < -PI) {
            targetHeading += 2*PI;
        }


        targetRot = targetHeading - heading;

        // Keep targetRot within [-PI, PI].
        if (targetRot > PI) {
            targetRot -= 2*PI;
        }
        else if (targetRot < -PI) {
            targetRot += 2*PI;
        }

        // Calculate target speeds.
        if (joy.axes[SZ] > 0) {
            rotSpeed = targetRot * MAX_ROT_SPEED / PI;
            transDir = atan2(joy.axes[SY], joy.axes[SX]) + targetRot + STRAFE_CORRECTION_GAIN*targetRot;

            if (isCartesian) { transDir += heading; }

            transSpeed = 2.5 * sqrt(pow(joy.axes[SX]/125, 2) + pow(joy.axes[SY]/125, 2)) * joy.axes[SZ] / 250.;
        }

        // Scale speeds by throttle value.
        rotSpeed   *= joy.axes[SZ]/250.;
        transSpeed *= joy.axes[SZ]/250.;

        // Calculate PWM duty cycles for the three wheels.
        calculate_pwm_outputs(rotSpeed, transDir, transSpeed);

        okayToFly = false;
    }
    else {
        // spln("Pilot not okay to fly.");
    }
}

void Pilot::die() {
    // ========================================================================
    // When communication is lost, pilot should set a bunch of stuff to safe
    // values.
    // ========================================================================
    okayToFly = false;
}

void Pilot::update_joystick_input(void) {
    // ========================================================================
    // Shift serial input values [0, 250] to correct range for each axis. Z
    // stays positive for ease of calculation.
    // ========================================================================
    joy.axes[SX] = (float) serInput[SX] - 125;   // [-125, 125]
    joy.axes[SY] = (float) serInput[SY] - 125;   // [-125, 125]
    joy.axes[ST] = (float) serInput[ST] - 125;   // [-125, 125]
    joy.axes[SZ] = (float) serInput[SZ];         // [   0, 250]

    // ========================================================================
    // Set button values. We utilize only the lower 7 bits, since doing
    // otherwise would cause overlaps with serial headers.
    // ========================================================================
    for (int i=0; i<7; i++) {
        joy.buttons[i]   = serInput[SB1] & (1<<i);
        joy.buttons[7+i] = serInput[SB2] & (1<<i);
    }
}

void Pilot::process_joystick_buttons(void) {
    // Toggle pilot mode.
    if (joy.buttons[BUTTON_PILOT_MODE_TOGGLE]) {
        isCartesian = true;
    }
    else {
        isCartesian = false;
    }

    // Reset targetHeading to heading if thumb button is pressed.
    if (joy.buttons[BUTTON_RESET_YAW]) {
        targetHeading = heading;
        targetHeading += joy.axes[ST]/125. * 1.5;
    }
}

