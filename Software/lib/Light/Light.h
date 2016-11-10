#ifndef LightController_h
#define LightController_h

#include <Config.h>
#include <Pins.h>
#include <Defines.h>
#include <Arduino.h>

class Light{

public:
    Light();

    //Set up the light sensors
    void init();

    //Read the light sensors
    void readLight();

    //get the angle to move from the Line
    double getAngle();

    //Average the angles over time
    void averageAngles();

private:
    int thresholds[19];
    int lightSensors[19];
    int detectedNumber;
    bool seeingWhite[19];

    double tempAngle;
    double finalDirection;

    int initalAngle;
    int newTempAngle;
    int newAngle;

};

#endif
