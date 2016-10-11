#ifndef RotationController_h
#define RotationController_h

#include <Config.h>
#include <Pins.h>
#include <Defines.h>
#include <Arduino.h>
#include <PixyI2C.h>
#include <Compass.h>

#define PIXY_CENTRE_X 160
#define PIXY_CENTRE_Y 100

class RotationController{

public:
    RotationController(){};
    bool getPixy(); //gets pixy stuff
    void calcPixy(); //calcs pixy stuff
    void calcRotation(); //calcs final stuff
    void getCompass(); //gets compass stuff
    int rotate(); //gives rotation

private:
    PixyI2C pixy;
    Compass compass;
    int rotationToAdd;
    int finalRotation

    double compassHeading;
    double newTarget;

};

#endif
