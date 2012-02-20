/*! \file omnikiwi.cpp
 *  \author Soo-Hyun Yoo
 *  \brief Main loop.
 *
 *  Details.
 */

#include <Servo.h>
#include <Wire.h>
#include "maze_solver.cpp"
#include "globals.h"
#include "telemetry.h"

int main(void) {
    init();   // For Arduino.

    // Begin Arduino services.
    Wire.begin();

    Serial.begin(BAUDRATE);

    Servo pwmDevice[3];
    pwmDevice[MOTOR_T].attach(MT_PWM);
    pwmDevice[MOTOR_R].attach(MR_PWM);
    pwmDevice[MOTOR_L].attach(ML_PWM);

    pinMode(MT_DIG, OUTPUT);
    pinMode(MR_DIG, OUTPUT);
    pinMode(ML_DIG, OUTPUT);

    // Initialize bot.
    MazeSolver mazer;

    // Variables

    unsigned long nextRuntime = micros();
    loopCount = 0;

    while (1) {
        if (micros() >= nextRuntime) {
            // ================================================================
            // System loop
            // ================================================================
            nextRuntime += MASTER_DT;   // Update next loop start time.

            // ================================================================
            // Control loop
            // ================================================================
            if (loopCount % CONTROL_LOOP_INTERVAL == 0) {
                mazer.run();
            }

            // ================================================================
            // Telemetry loop
            // ================================================================
            if (loopCount % TELEMETRY_LOOP_INTERVAL == 0) {
                sendTelemetry(nextRuntime);
            }

            loopCount++;
            loopCount = loopCount % 1000;
        } // endif
    } // endwhile

    return 0;
}

