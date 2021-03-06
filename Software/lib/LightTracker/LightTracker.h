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

    double getDirection(double lightAngle, double ballAngle, double compassAngle);
    int getSpeed();
private:
    double adjustLightReturn(double lightAngle, double compassAngle);
    double calulateBounds(double lightAngle, double ballAngle);

    // for tracking
    double lineInitDirection = 0;

    // line memeory
    bool wasSeeingLine = false;
    double lastAngle = 0;

    // speed
    int speed;


};
#endif
