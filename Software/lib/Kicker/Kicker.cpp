#include <Kicker.h>

#define KICKER_PIN 0
#define KICKER_DELAY 2000L
#define LIGHTGATE_PIN 0
#define LIGHTGATE_THRESHOLD 100

void Kicker::Kicker(){
    pinMode(KICKER_PIN, OUTPUT);
    digitalWrite(KICKER_PIN, HIGH);
    pinMode(LIGHTGATE_PIN, INPUT);
}

kickerStatus Kicker::kickerReady(){
    long currentMSec = micros();
    if((currentMSec - lastKick) >= KICKER_DELAY){
        status = kickerStatus::waitingForLightGate;
        return kickerStatus::waitingForLightGate;
    }
    else{
        status = kickerStatus::waitingForCharge;
        return kickerStatus::waitingForCharge;
    }
}

kickerStatus Kicker::checkLightGate(){
    if(analogRead(LIGHTGATE_PIN) <= LIGHTGATE_THRESHOLD && status == kickerStatus::waitingForLightGate){
        status = kickerStatus::ready;
        return kickerStatus::ready;
    }
}

void Kicker::kickBall(){
    if(status == kickerStatus::ready){
        digitalWrite(KICKER_PIN, LOW);
        digitalWrite(KICKER_PIN, HIGH);
        lastKick = micros();
    }
    else{
        status = kickerStatus::notReady;
    }
}
