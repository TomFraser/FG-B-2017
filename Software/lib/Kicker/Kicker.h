#ifndef Kicker_h
#define Kicker_h

#include <Arduino.h>

enum kickerStatus {
    unknown,
    notReady,
    waitingForLightGate,
    waitingForCharge,
    ready
};

class Kicker{
public:
    Kicker();
    kickerStatus kickerReady();
    kickerStatus checkLightGate();
    void kickBall();
private:
    kickerStatus status = unknown;
    long currentMSec, lastKick;

};

#endif
