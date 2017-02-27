#ifndef ReadTSOPS_h
#define ReadTSOPS_h

#include <Config.h>
#include <Pins.h>
#include <Defines.h>
#include <Arduino.h>
#include <math.h>

class ReadTSOPS{

public:
    ReadTSOPS();

    //Read the Tsops
    void read();

    //Reset the Tsops by dropping power
    void reset();

    //Stop reading tsops, error has occured
    void stop();

    //Calculate a tangent to move on to orbit around the ball
    int moveTangent();

    //Find the strength for the ball and determine how to orbit
    double findStrength();

    int bestSensor;
    double angleToBall;

private:
    int sensors[12] = {1,2,3,4,5,6,7,8,9,15,16,17};
    int values[12];
    int index;
    int mod(int x, int m);

};

#endif
