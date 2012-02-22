/*! \file omnikiwi.cpp
 *  \author Soo-Hyun Yoo
 *  \brief Main loop.
 *
 *  Details.
 */

#include <Wire.h>
#include "maze_solver.cpp"
#include "pilot.cpp"
#include "globals.h"
#include "telemetry.h"

int main(void) {
    init();   // For Arduino.

    // Begin Arduino services.
    Wire.begin();

    Serial.begin(BAUDRATE);

    pinMode(MT_DIG, OUTPUT);
    pinMode(MR_DIG, OUTPUT);
    pinMode(ML_DIG, OUTPUT);

    // Initialize bot.
    MazeSolver mazer;
    Pilot pilot;

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
                pilot.listen();
                pilot.fly();
                mazer.run();

                analogWrite(MT_PWM, analogOut[MOTOR_T]);
                analogWrite(MR_PWM, analogOut[MOTOR_R]);
                analogWrite(ML_PWM, analogOut[MOTOR_L]);

                digitalWrite(MT_DIG, digOut[MOTOR_T]);
                digitalWrite(MR_DIG, digOut[MOTOR_R]);
                digitalWrite(ML_DIG, digOut[MOTOR_L]);
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

