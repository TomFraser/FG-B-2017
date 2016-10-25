#ifndef Kicker_h
#define Kicker_h

#include <Arduino.h>
#include <Config.h>
#include <Pins.h>

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
    void kickerReady();
    void checkLightGate();
    void kickBall();
private:
    kickerStatus status;
    long currentMSec, lastKick;

};

#endif
