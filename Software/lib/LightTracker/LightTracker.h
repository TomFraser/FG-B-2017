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

    void update(double absLight, double absMove, double moveSpeed, double absRawBall, int numSensors);
    int getSpeed();
    double getDirection();
    bool getSeeingLine();
private:
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
