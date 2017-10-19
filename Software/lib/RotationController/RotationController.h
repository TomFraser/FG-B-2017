#ifndef RotationController_h
#define RotationController_h

#include <Config.h>
#include <Pins.h>
#include <i2c_t3.h>
#include <Defines.h>
#include <Arduino.h>
// #include <PixyI2C.h>

class RotationController{

public:
    RotationController();

    void init();

    //Gets the pixy information
    bool getPixy();

    //Calulates the pixy and which direction to go
    double calcPixy();

    //Calculates the rotation needed to face the centre of the goal
    void calcRotation();

    //Uses compass library to find the compass roataion required
    double getCompass();

    //The final rotation to add to the motors
    double rotate(int rotationData);

    double rawCompass();

    double PIDRotation(double rotationIn);

    long lastTime = 0;
    double lastAngle = 0;
    int prevPixy = 0;

private:
    // PixyI2C pixy;
    int rotationToAdd;
    int finalRotation;
    double prevReturn;
    long prevTime = 0;

    int blockHeight, blockWidth, blockX, blockY;

    double compassHeading, absCompassHeading;
    double newTarget;

};

#endif
