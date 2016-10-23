#ifndef DirectionController_h
#define DirectionController_h

// #include <Config.h>
// #include <Pins.h>
// #include <Defines.h>
#include <Arduino.h>
#include <Motor.h>
#include <Light.h>
#include <ReadTSOPS.h>
#include <RotationController.h>

#define angToRad 0.01745329251
#define radToAng 57.2957795131

class DirectionController{

public:
    DirectionController();
    void calcMotors(double angle, double rotation);
    void calcMotors(double angle, double rotation, int dirNum); //used to limit the nuber of directions the robot can move in.
    lightStruct calcLight();
    void calcTsops();
    void combine();

private:
    int angleArray[3] = {60, 180, 300};

    double direction;

    Motor motorA = Motor(1,2,3,0);
    Motor motorB = Motor(1,2,3,0);
    Motor motorC = Motor(1,2,3,0);

    Light light = Light();

    double lightAngle;
    lightStruct values;

    ReadTSOPS tsops = ReadTSOPS();

    double tsopAngle;

    RotationController rotationController = RotationController();
};

struct lightStruct {
    bool seeing;
    double angle;
};

#endif
