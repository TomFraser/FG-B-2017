#ifndef LightController_h
#define LightController_h

// #include <Config.h>
// #include <Pins.h>
// #include <Defines.h>
#include <Arduino.h>

class Light{

public:
    Light();
    void init();
    void readLight();
    double getAngle();
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
