#ifndef LightController_h
#define LightController_h

#include <Config.h>
#include <Pins.h>
#include <Defines.h>
#include <Arduino.h>

class Light{

public:
    Light();

    //Set up the light sensors
    void init();

    //Read the light sensors
    void readLight();

    //Identify clusters of lightsensors seeing the Line
    void findClusters();


private:
    //init stuff
    int thresholds[19];
    int lightSensors[19];

    //for reading light
    int detectedNumber;
    bool seeingWhite[19];

    //cluster stuff

};

struct cluster{
  bool exist;
  int begin;
  int end;
};
#endif
