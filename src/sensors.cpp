/*! \file sensors.cpp
 *  \author Soo-Hyun Yoo
 *  \brief Read sensors.
 */

#include "sensors.h"

Sensors::Sensors() {
    for (int i=0; i<NUM_OF_LEDS; i++) {
        pinMode(anodePins[i], OUTPUT);
        pinMode(cathodePins[i], OUTPUT);
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
    // between first and second readings.
    ledReadings[ledNum] = chargeReadings[ledNum] - analogRead(ledNum);

    // Maybe try taking multiple readings?

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

