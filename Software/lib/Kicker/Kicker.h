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
    //Check if the kicker is ready to kick
    void kickerReady();
    //Check if the light gate is seeing the ball
    void checkLightGate();
    //Kick the ball
    void kickBall();
    bool controlKick();
    bool hasBall();
private:
    kickerStatus status;
    long currentMSec, lastKick;

};

#endif
