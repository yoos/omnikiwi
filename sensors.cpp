/*! \file sensors.cpp
 *  \author Soo-Hyun Yoo
 *  \brief Read sensors.
 */

#include "sensors.h"

Sensors::Sensors() {
    pinMode(13, OUTPUT);
    pinMode(12, INPUT);


    // DEPRECATED LED SENSOR CODE
    // Disable all pullup resistors.
    //_SFR_IO8(0x35) |= 0x10;

    //digitalWrite(LED_ANODE, LOW);
    //pinMode(LED_ANODE, OUTPUT);
    //for (int i=0; i<NUM_OF_LEDS; i++) {
    //    pinMode(cathodePins[i], INPUT);
    //}
}

void Sensors::read() {
    if (digitalRead(12) == LOW) {
        digitalWrite(13, LOW);
    }
    else {
        digitalWrite(13, HIGH);
    }


    // LED sensor code from Arduino playground
    // Charge LEDs (reverse bias)
    for (int i=0; i<NUM_OF_LEDS; i++) {
        digitalWrite(cathodePins[i], HIGH);
    }
    digitalWrite(LED_ANODE, LOW);

    // Take first analog readings from cathode pins.
    for (int i=0; i<NUM_OF_LEDS; i++) {
        pinMode(cathodePins[i], INPUT);
        digitalWrite(cathodePins[i], LOW);
    }
    for (int i=0; i<NUM_OF_LEDS; i++) {
        ledReadings[i] = analogRead(i);
    }

    // Let LEDs discharge   TODO: Make this non-locking! Maybe read() should
    // toggle between charge and read?
    delay(40);

    // Take second readings and calculate voltage drop between first and second
    // readings.
    for (int i=NUM_OF_LEDS-1; i>-1; i--) {   // Reverse order to reduce crosstalk.
        ledReadings[i] -= analogRead(i);
    }

    // Discharge LEDs (forward bias)
    for (int i=0; i<NUM_OF_LEDS; i++) {
        pinMode(cathodePins[i], OUTPUT);
        digitalWrite(cathodePins[i], LOW);
    }
    digitalWrite(LED_ANODE, HIGH);



    // DEPRECATED LED SENSOR CODE
    //// Turn on LEDs (forward bias)
    //for (int i=0; i<NUM_OF_LEDS; i++) {
    //    digitalWrite(LED_ANODE, HIGH);
    //    pinMode(cathodePins[i], OUTPUT);
    //    digitalWrite(cathodePins[i], LOW);
    //}

    //// Charge LEDs (reverse bias)
    //for (int i=0; i<NUM_OF_LEDS; i++) {
    //    digitalWrite(LED_ANODE, LOW);
    //    digitalWrite(cathodePins[i], HIGH);
    //}

    //// Take first analog readings from cathode pins.
    //for (int i=0; i<NUM_OF_LEDS; i++) {
    //    pinMode(cathodePins[i], INPUT);
    //}
    //for (int i=0; i<NUM_OF_LEDS; i++) {
    //    ledReadings[i] = analogRead(i);
    //}

    //// Let LEDs discharge   TODO: Make this non-locking!
    //delay(40);

    //// Take second readings and calculate voltage drop between first and second
    //// readings.
    //for (int i=NUM_OF_LEDS-1; i>-1; i--) {   // Reverse order to reduce crosstalk.
    //    ledReadings[i] -= analogRead(i);
    //    pinMode(cathodePins[i], OUTPUT);
    //    digitalWrite(cathodePins[i], LOW);
    //}
}

