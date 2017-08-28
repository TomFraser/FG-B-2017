#ifndef LightTracker_h
#define LightTracker_h

#include <Config.h>
#include <Pins.h>
#include <Defines.h>
#include <Arduino.h>

class LightTracker{

public:
    LightTracker();

    double getDirection(double lightAngle, double tsopAngle, double compassAngle);
private:
    // for tracking
    double lineInitDirection;
    bool seeingLine = false;

};
#endif
