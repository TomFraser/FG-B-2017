#ifndef Light_new_h
#define Light_new_h

#include <Arduino.h>
#include <Math.h>
#include <fgbcommon.h>

class Light{
private:
    bool lightReadings[19] = {};
    int calibrationReading[19] = {};
    int lightSensors[19] = {/* pins to sensors hereeeee*/};
    int angle = 0;
    int sensorCounter = 0;
    double avgAngle = 0;
    double difference[4];
    double curentLow = 360.00;
    int chosenSide = 0;

    enum robotLocation{
        field,
        online_left,
        online_right,
        online_top,
        online_back,
        overline_left,
        overline_right,
        overline_top,
        overline_back,
        lost
    };
    enum lineLocation{
        standard,
        small_left,
        small_right,
        small_top,
        small_back,
        big_left,
        big_right,
        big_top,
        big_back,
        gone
    };
    robotLocation currLocation = regular;
    robotLocation prevLocation = regular;
    robotLocation locations[4] = {small_top, small_right, small_back, small_left};
    robotLocation locr = regular;

    struct lineDir{
        double lineStrength,
        double angle
    };

    lineDir averageSensors(int array);
    lineLocation finalizeLine(lineDir line);

public:
    Light(){};
    void setThreshold();
    void read();
    void sort();
    robotLocation getLocation();
    robotLocation getPrevLocation();
    void getRobotLocation();
    void adjust();

};

#endif
