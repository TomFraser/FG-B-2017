#ifndef RotationController_h
#define RotationController_h

#include <Config.h>
#include <Pins.h>
#include <Defines.h>
#include <Arduino.h>
#include <PixyI2C.h>
#include <Compass.h>

class RotationController{

public:
    RotationController();

    //Gets the pixy information
    bool getPixy();

    //Calulates the pixy and which direction to go
    void calcPixy();

    //Calculates the rotation needed to face the centre of the goal
    void calcRotation();

    //Uses compass library to find the compass roataion required
    void getCompass();

    //The final rotation to add to the motors
    double rotate();

private:
    PixyI2C pixy;
    Compass compass = Compass();
    int rotationToAdd;
    int finalRotation;

    int blockHeight, blockWidth, blockX, blockY;

    double compassHeading;
    double newTarget;

};

#endif
