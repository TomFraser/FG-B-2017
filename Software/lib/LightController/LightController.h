#ifndef LightController_h
#define LightController_h

#include <Config.h>
#include <Arduino.h>

class LightController{

public:
    LightController();
    void determineThresholds();
    void letsDoSomeGeometry();

private:
    int thresholds[19];
    int lightSensors[19];

};

#endif
