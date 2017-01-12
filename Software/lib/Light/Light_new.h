#ifndef Light_new_h
#define Light_new_h

#include <Arduino.h>
#include <Math.h>

class Light{
private:
    bool lightReadings[19] = {};
    int calibrationReading[19] = {};
    int lightSensors[19] = {/* pins to sensors hereeeee*/};

    enum robotLocation{
        regular,
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

public:
    Light(){};
    void setThreshold();
    void read();
    void sort();
    robotLocation getLocation();
    robotLocation getPrevLocation();

};

#endif
