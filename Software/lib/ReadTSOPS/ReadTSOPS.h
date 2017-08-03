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

    void read();

    void reset();

    void stop();

    int moveTangent();

    double findStrength();

    int bestSensor;
    double angleToBall;

private:
    int sensors[12] = {1,2,3,4,5,6,7,8,9,15,16,17};
    int values[12];
    int previousIndex = 0;
    int value_index, previousValue_index, scaledStrength, scaledAngle, index;
    double scaled90;
    int mod(int x, int m);
    double correctOrbit(double angleIn, bool useFirst);
    double correctedOrbit(double angleIn);

};

#endif
