#ifndef DEBUG_H
#define DEBUG_H

#include <Config.h>
#include <Defines.h>
#include <Pins.h>
#include <Arduino.h>

class debugClass{
public:
    debugClass(){};
    void log(int value);
    void log(double value);
    void log(bool value);
    void logValue(const String& title, int value);
    void logValue(const String& title, double value);
    void logValue(const String& title, bool value);
    void logString(const String& title);
    void watchVariable();
private:

};

#endif
