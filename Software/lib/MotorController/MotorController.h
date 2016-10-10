#ifndef MotorController_h
#define MotorController_h

#include <Config.h>
#include <Arduino.h>
#include <Motor.h>

#define angToRad 0.01745329251
#define radToAng 57.2957795131

class MotorController{

public:
    MotorController();
    void setAngle(int angle);
    void setAnlge(int angle, int dirNum); //used to limit the nuber of directions the robot can move in.

private:
    int angleArray[3] = {60, 180, 300};

    double direction;

    Motor motorA = Motor(1,2,3,0);
    Motor motorB = Motor(1,2,3,0);
    Motor motorC = Motor(1,2,3,0);
};

#endif
