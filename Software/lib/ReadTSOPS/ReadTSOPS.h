#ifndef ReadTSOPS_h
#define ReadTSOPS_h

 #include <Config.h>
#include <Pins.h>
#include <Defines.h>
#include <Arduino.h>
#include <Math.h>

class ReadTSOPS{

public:
    ReadTSOPS();
    void readMode(int mode);
    void read();
    void reset();
    void stop();
    int moveTangent();
    double findStrength();

    int bestSensor;
    double angleToBall;

private:
    int sensors[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
    int values[12];
    int index;
    int mod(int x, int m);

};

#endif
