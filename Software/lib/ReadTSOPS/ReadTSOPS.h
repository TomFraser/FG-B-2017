#ifndef ReadTSOPS_h
#define ReadTSOPS_h

 #include <Config.h>
#include <Pins.h>
#include <Defines.h>
#include <Arduino.h>

class ReadTSOPS{

private:
    int sensors[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
    int values[12];
    int index;

public:
    ReadTSOPS();
    void readMode(int mode);
    void read();
    void reset();
    void stop();
    int moveTangent();

    int bestSensor;
    double angleToBall;
};

#endif
