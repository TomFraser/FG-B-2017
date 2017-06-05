#include <Debug.h>

void debugClass::log(int value){
    #if DEBUG
    Serial.println(value);
    #endif
}

void debugClass::log(double value){
    #if DEBUG
    Serial.println(value);
    #endif
}

void debugClass::log(bool value){
    #if DEBUG
    Serial.println(value);
    #endif
}

void debugClass::logValue(const String& title, int value){
    #if DEBUG
    Serial.print(title);
    Serial.println(value);
    #endif
}

void debugClass::logValue(const String& title, double value){
    #if DEBUG
    Serial.print(title);
    Serial.println(value);
    #endif
}

void debugClass::logValue(const String& title, bool value){
    #if DEBUG
    Serial.print(title);
    Serial.println(value);
    #endif
}

void debugClass::watchVariable(){
    //This will take some time, dynamically print a variable based upon a change in value
}
