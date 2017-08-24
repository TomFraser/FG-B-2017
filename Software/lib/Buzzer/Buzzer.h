#ifndef Buzzer_h
#define Buzzer_h

#include <Arduino.h>
#include <Config.h>
#include <Pins.h>
#include <Defines.h>

//
// The Buzzer Class
//
class Buzzer{

public:
    void playTone(int miliS);
    void errorTone();
    void readyTone();
private:

};

void Buzzer::playTone(int miliS){
    digitalWrite(BUZZER_PIN, HIGH);
    delay(miliS);
    digitalWrite(BUZZER_PIN, LOW);
}

void Buzzer::errorTone(){
    digitalWrite(BUZZER_PIN, HIGH);
}

void Buzzer::readyTone(){
    playTone(500);
    delay(500);
    playTone(500);
}

#endif
