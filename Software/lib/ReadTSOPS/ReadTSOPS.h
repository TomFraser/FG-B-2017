#ifndef ReadTSOPS_h
#define ReadTSOPS_h

#include <Config.h>
#include <Pins.h>
#include <Defines.h>
#include <Arduino.h>
#include <math.h>
#include <fgbcommon.h>

class ReadTSOPS{

public:
    ReadTSOPS();

    void read();
    void reset();
    void stop();
    void moveAngle();
    int getAngle();
    double calculateStrength();

    int bestSensor, secondSensor, thirdSensor;
    double angleToBall;

private:
    int bestAngle;
    int sensors[12] = {1,2,3,4,5,6,7,8,9,15,16,17};
    int values[12];
    int sensorOrder[12];
    int previousIndex = 0;
    int value_index, previousValue_index, scaledStrength, scaledAngle, index, tsop3, tsop2;
    double scaled90;

    int mod(int x, int m);
    double calculateOrbitSimple(double angleIn, bool useFirst);
    double calculateOrbitComplex(double angleIn);
    double calculateTSOPAverage();
};

#endif
