/*! \file omnikiwi.cpp
 *  \author Soo-Hyun Yoo
 *  \brief Main loop.
 *
 *  Details.
 */

#include <Wire.h>
#include "maze_solver.cpp"
#include "pilot.cpp"
#include "sensors.cpp"
#include "globals.h"
#include "telemetry.h"

int main(void) {
    init();   // For Arduino.

    // Begin Arduino services.
    //Wire.begin();

    Serial.begin(BAUDRATE);

    pinMode(MT_DIG, OUTPUT);
    pinMode(MR_DIG, OUTPUT);
    pinMode(ML_DIG, OUTPUT);

    // Initialize bot.
    MazeSolver mazer;
    Sensors sensors;
    Pilot pilot;

    // Variables

    uint64_t nextRuntime = micros();
    loopCount = 0;

    while (1) {
        if (micros() >= nextRuntime) {
            // ================================================================
            // System loop
            // ================================================================
            nextRuntime += MASTER_DT;   // Update next loop start time.

            // ================================================================
            // Sensor loop
            //
            // WARNING: This loop is extremely time-sensitive! Make sure the
            // looptime never exceeds MASTER_DT!
            // ================================================================
            for (int i=0; i<NUM_OF_LEDS; i++) {
                if (loopCount % SENSOR_LOOP_INTERVAL == i) {
                    // Charge up the LED two pins down the list since a delay
                    // of 16 ms seems to work well while our master loop time
                    // is 8 ms. Do this before readLED() to reduce noise! TODO:
                    // Figure out why doing this before readLED() makes the
                    // readings less noisy.
                    sensors.chargeLED((i+2) % NUM_OF_LEDS);

                    // Read requested LED.
                    sensors.readLED(i);
                }
            }

            // ================================================================
            // Control loop
            // ================================================================
            if (loopCount % CONTROL_LOOP_INTERVAL == 0) {
                //mazer.run();
                pilot.fly();

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
                pilot.listen();
            }
            if (loopCount % TELEMETRY_LOOP_INTERVAL == 1) {
                sendTelemetry(nextRuntime);
            }

            loopCount++;
            loopCount = loopCount % 1000;
        } // endif
    } // endwhile

    return 0;
}

