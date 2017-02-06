#ifndef DirectionController_h
#define DirectionController_h

#include <Config.h>
#include <Pins.h>
#include <Defines.h>
#include <Arduino.h>
#include <Motor.h>
#include <Light.h>
#include <ReadTSOPS.h>
#include <RotationController.h>

struct lightStruct {
    bool seeing;
    double angle;
};

class DirectionController{

public:
    DirectionController();

    //Calculate motor angles
    void calcMotors(double angle, double rotation);

    //Calculate motor angles
    void calcMotors(double angle, double rotation, int dirNum);

    //Calculate lightsensors
    lightStruct calcLight();

    //Combines lightsensors and tsop direction
    void move(double angle);

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

    RotationController rotationController = RotationController();
};


#endif
