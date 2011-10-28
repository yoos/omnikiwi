#include "Watchdog.h"

Watchdog::Watchdog(int timeout) {
    dogLife = timeout;
    started = false;
}

void Watchdog:Start() { // If this runs too late, dogLife may already have ended.
    if (!started)
        time = millis();
    if (millis() - time < dogLife) {
        isAlive = true;
    else
        isAlive = false;
    }
}

void Watchdog::Feed(char dogBone) {
    if (dogBone == DOGBONE) {
        time = millis();
    }
}

