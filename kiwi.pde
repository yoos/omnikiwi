// Author: Soo-Hyun Yoo

#include "FooMotor.h"
#include "Driver.h"
#include "Debounce.h"
#include "Communication.h"
#include "Watchdog.h"

#define MOTORS_ENABLE 2

float dir, rot;

void setup () {
    Serial.begin(4800);
    Serial.println("Start!");
    pinMode(MOTORS_ENABLE, OUTPUT);

    Watchdog kiwiWatch(200);

    FooMotor ma(3, 4);
    FooMotor mb(6, 7);
    FooMotor mc(5, 8);

    Driver kiwiDriver(ma, mb, mc);
}

void loop () {
    
    kiwiDriver.Drive(dir, rot);

    if (debounce(digitalRead(BUTTON_PIN), buttonPinLast))
        blinkOn = !blinkOn;
    if (blinkOn)
        digitalWrite(BLINK_PIN, HIGH);
    else
        digitalWrite(BLINK_PIN, LOW);

    if (millis() - prevMillis > INTERVAL)
    {
        prevMillis = millis();
        if (fadeValue >= FADE_TOP || fadeValue <= 0)
            fading = !fading;
        if (fading)
            fadeValue -= 1;
        else
            fadeValue += 1;
    }
    analogWrite(FADE_PIN, fadeValue);
    Serial.println(analogRead(ENCODER_PIN));

}


