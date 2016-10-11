#ifndef LightController_h
#define LightController_h

#include <Config.h>
#include <Arduino.h>

class Light{

public:
    Light();
    void init();
    void readLight();
    int getAngle();
    void recalcAngle(); //Used when in the loop of moving back into the field.

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

    void averageAngles();

};

#endif
