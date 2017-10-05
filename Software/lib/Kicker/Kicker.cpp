#include <Kicker.h>

Kicker::Kicker(){
    pinMode(KICKER_PIN, OUTPUT);
    digitalWrite(KICKER_PIN, LOW);
    pinMode(LIGHTGATE_PIN, INPUT);
    status = kickerStatus::unknown;
}

void Kicker::kickerReady(){
    long currentMSec = micros();
    if((currentMSec - lastKick) >= KICKER_DELAY){
        status = kickerStatus::waitingForLightGate;
    }
    else{
        status = kickerStatus::waitingForCharge;
    }
}

void Kicker::checkLightGate(){
    if(analogRead(LIGHTGATE_PIN) <= KICK_THRESHOLD && status == kickerStatus::waitingForLightGate){
        status = kickerStatus::ready;
    }
}

void Kicker::kickBall(){
    digitalWrite(KICKER_PIN, HIGH);
    delay(10); //To Change in the future to a loop system. This will slow the robot down.
    digitalWrite(KICKER_PIN, LOW);
    lastKick = micros();
    status = kickerStatus::notReady;
}

bool Kicker::controlKick(){
    kickerReady();
    checkLightGate();
    kickBall();
}

bool Kicker::hasBall(){
    if(analogRead(LIGHTGATE_PIN) <= KICK_THRESHOLD){
        return true;
    }else{
        return false;
    }
}
