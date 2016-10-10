#ifndef TsopController_h
#define TsopController_h

#include <Config.h>
#include <ReadTSOPS.h>
#include <Arduino.h>

class TsopController{

public:
    TsopController(){};
    uint16_t activateTsop();

private:
    ReadTSOPS TSOPS;
    int bestSensor;
    uint16_t toSend;
};

#endif
