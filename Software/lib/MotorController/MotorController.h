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
    void setAnlge(int angle, int dirNum);

private:
    int angleArray[3] = {60, 180, 300};

};

#endif
