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

// Plays a tone for a amount of time
void Buzzer::playTone(int miliS){
    digitalWrite(BUZZER_PIN, HIGH);
    delay(miliS);
    digitalWrite(BUZZER_PIN, LOW);
}

// Plays a tone to signal an error until the Teensy loses power
void Buzzer::errorTone(){
    digitalWrite(BUZZER_PIN, HIGH);
}

// Plays two tones for 1.5 seconds to signal when the robot is ready to run
void Buzzer::readyTone(){
    playTone(500);
    delay(500);
    playTone(500);
}

#endif
