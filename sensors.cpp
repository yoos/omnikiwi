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

    // DEPRECATED LED SENSOR CODE
    // Disable all pullup resistors.
    //_SFR_IO8(0x35) |= 0x10;
}

void Sensors::read() {
    // Charge LEDs (reverse bias)
    for (int i=0; i<NUM_OF_LEDS; i++) {
        digitalWrite(cathodePins[i], HIGH);
        digitalWrite(anodePins[i], LOW);
    }

    // Should I try a delay here?

    // Take first analog readings from cathode pins.
    for (int i=0; i<NUM_OF_LEDS; i++) {
        pinMode(cathodePins[i], INPUT);
        digitalWrite(cathodePins[i], LOW);   // Disable pullup resistor.
        ledReadings[i] = analogRead(i);
        // Should I try a delay after the analogRead()?
    }

    // Let LEDs discharge   TODO: Make this non-locking! Maybe read() should
    // toggle between charge and read?
    // Making the delay too low makes the readings drift.
    delay(LED_DISCHARGE_TIME);

    // Take second readings and calculate voltage drop between first and second
    // readings.
    //for (int i=NUM_OF_LEDS-1; i>-1; i--) {   // Reverse order to reduce crosstalk.
    for (int i=0; i<NUM_OF_LEDS; i++) {
        ledReadings[i] -= analogRead(i);
        // Should I try a delay after the analogRead()?
    }

    // Fully discharge LEDs (forward bias)
    for (int i=0; i<NUM_OF_LEDS; i++) {
        pinMode(cathodePins[i], OUTPUT);
        digitalWrite(cathodePins[i], LOW);   // Is this line necessary?
        digitalWrite(anodePins[i], HIGH);
    }
}

