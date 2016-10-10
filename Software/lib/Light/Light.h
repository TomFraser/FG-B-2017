#ifndef LightController_h
#define LightController_h

#include <Config.h>
#include <Arduino.h>

class Light{

public:
    Light();
    void init();
    void readLight();

private:
    int thresholds[19];
    int lightSensors[19];

    bool seeingWhite[19];

};

#endif
