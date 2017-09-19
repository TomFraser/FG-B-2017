#ifndef Blink_h
#define Blink_h

#include <Arduino.h>

long initTime;
int led;

void blink(){
    Serial.println(led);
    if(millis() > initTime + 1000){
        if(led == 0){
            digitalWrite(13, HIGH);
            led = 1;
            initTime = millis();
        }else{
            digitalWrite(13, LOW);
            led = 0;
            initTime = millis();
        }
    }
}

#endif
