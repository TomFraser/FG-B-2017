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

    void update(double lightAngle, double moveAngle, bool isBallAngle, double compassAngle);
    int getSpeed();
    double getDirection();
    bool getSeeingLine();
private:
    double adjustDirectionReturn(double lightAngle, double compassAngle);
    double calulateBounds(double lightAngle, double ballAngle);

    // for tracking
    double lineInitDirection = 0;

    // line memeory
    bool wasSeeingLine = false;
    double lastAngle = 0;

    // speed
    int speed;

    // direction
    double direction;


};
#endif
