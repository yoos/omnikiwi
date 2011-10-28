#ifndef WATCHDOG_H
#define WATCHDOG_H

class Watchdog {
    bool started;
    int time;
    int dogLife;
    bool isAlive;

public:
    Watchdog();
    void start(int);
    void Feed(char);

#endif // WATCHDOG_H

