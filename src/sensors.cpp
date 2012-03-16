/*! \file sensors.cpp
 *  \author Soo-Hyun Yoo
 *  \brief Read sensors.
 */

#include "sensors.h"

Sensors::Sensors() {
    for (int i=0; i<NUM_OF_LEDS; i++) {
        pinMode(anodePins[i], OUTPUT);
        pinMode(cathodePins[i], OUTPUT);

        #ifdef SENSORS_LPF_DEPTH
        lpfIndex[i] = 0;
        for (int j=0; j<SENSORS_LPF_DEPTH; j++) {
            lpfVal[i][j] = 0;
        }
        #endif // SENSORS_LPF_DEPTH

        chargeReadings[i] = 0;
        ledReadings[i] = 0;
        ledFiltered[i] = 0;
    }
}

/*! Charge LED and take first analog reading.
 *
 *  \param ledNum Index of LED to charge and read.
 */
void Sensors::chargeLED(int ledNum) {
    // Reverse bias LED.
    digitalWrite(cathodePins[ledNum], HIGH);
    digitalWrite(anodePins[ledNum], LOW);

    // Take first analog reading from cathode pin.
    pinMode(cathodePins[ledNum], INPUT);
    digitalWrite(cathodePins[ledNum], LOW);   // Disable pullup resistor.
    chargeReadings[ledNum] = analogRead(ledNum);
}

/*! Take second analog reading and discharge LED.
 *
 *  \param ledNum Index of LED to read and discharge.
 */
void Sensors::readLED(int ledNum) {
    // Take second analog reading from cathode pin and calculate voltage drop
    // between first and second readings. Sometimes, this drop is insanely big
    // -- ignore those.
    uint16_t tmp = chargeReadings[ledNum] - analogRead(ledNum);
    ledReadings[ledNum] = (tmp < LED_MAX_SANE_READING) ? tmp : ledReadings[ledNum];

    // Low-pass filter.
    #ifdef SENSORS_LPF_DEPTH
    lpfVal[ledNum][lpfIndex[ledNum]] = ((float) ledReadings[ledNum]) / SENSORS_LPF_DEPTH;

    ledFiltered[ledNum] = 0;
    for (int i=0; i<SENSORS_LPF_DEPTH; i++) {
        ledFiltered[ledNum] += lpfVal[ledNum][i];
    }
    lpfIndex[ledNum] = (lpfIndex[ledNum] + 1) % SENSORS_LPF_DEPTH;   // Increment index by 1 and loop back from SENSORS_LPF_DEPTH.

    #else
    ledFiltered[ledNum] = ledReadings[ledNum];
    #endif // SENSORS_LPF_DEPTH

    // Forward bias LED.
    pinMode(cathodePins[ledNum], OUTPUT);
    digitalWrite(anodePins[ledNum], HIGH);
}

void Sensors::read() {

    // DEPRECATED 2/24/12
    //// Charge LEDs (reverse bias)
    //for (int i=0; i<NUM_OF_LEDS; i++) {
    //    digitalWrite(cathodePins[i], HIGH);
    //    digitalWrite(anodePins[i], LOW);
    //}

    //// Should I try a delay here?

    //// Take first analog readings from cathode pins.
    //for (int i=0; i<NUM_OF_LEDS; i++) {
    //    pinMode(cathodePins[i], INPUT);
    //    digitalWrite(cathodePins[i], LOW);   // Disable pullup resistor.
    //    ledReadings[i] = analogRead(i);
    //    // Should I try a delay after the analogRead()?
    //}

    //// Let LEDs discharge   TODO: Make this non-locking! Maybe read() should
    //// toggle between charge and read?
    //// Making the delay too low makes the readings drift.
    ////delay(LED_DISCHARGE_TIME);

    //// Take second readings and calculate voltage drop between first and second
    //// readings.
    ////for (int i=NUM_OF_LEDS-1; i>-1; i--) {   // Reverse order to reduce crosstalk.
    //for (int i=0; i<NUM_OF_LEDS; i++) {
    //    ledReadings[i] -= analogRead(i);
    //    // Should I try a delay after the analogRead()?
    //}

    //// Fully discharge LEDs (forward bias)
    //for (int i=0; i<NUM_OF_LEDS; i++) {
    //    pinMode(cathodePins[i], OUTPUT);
    //    digitalWrite(cathodePins[i], LOW);   // Is this line necessary?
    //    digitalWrite(anodePins[i], HIGH);
    //}
}

