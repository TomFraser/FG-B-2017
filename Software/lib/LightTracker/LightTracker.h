#ifndef LightTracker_h
#define LightTracker_h

#include <Config.h>
#include <Pins.h>
#include <Defines.h>
#include <Arduino.h>
#include <Common.h>

class LightTracker{

public:
    LightTracker();

    double getDirection(double lightAngle, double tsopAngle, double compassAngle);
private:
    // for tracking
    double lineInitDirection = 0;

    // line memeory
    bool wasSeeingLine = false;
    double lastAngle = 0;


};
#endif
