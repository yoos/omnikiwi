#ifndef DEBOUNCE_H
#define DEBOUNCE_H

bool debounce (bool currentState, bool &lastState) {
    if (currentState != lastState)
        return (lastState = currentState);
    else
        return false;
}

#endif // DEBOUNCE_H

