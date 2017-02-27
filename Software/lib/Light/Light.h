#ifndef LightController_h
#define LightController_h

#include <Config.h>
#include <Pins.h>
#include <Defines.h>
#include <Arduino.h>

struct cluster{
  bool exist;
  int begin;
  int end;
};

class Light{

public:
    Light();

    //Set up the light sensors
    void init();

    //Dump Light Values
    void getVals(int *);

    //Read the light sensors
    void readLight();

    //Identify clusters of lightsensors seeing the Line
    cluster singleCluster(int, int);

    //Find all the clusters
    void findClusters(cluster *);

    //Get angles
    double getAngle();




private:
    //init stuff
    int thresholds[19];
    int lightSensors[19];

    //for reading light
    int detectedNumber;
    bool seeingWhite[19] = {false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false};

    //cluster stuff
    double lightCoords[19][2] = {
        {light1x, light1y},
        {light2x, light2y},
        {light3x, light3y},
        {light4x, light4y},
        {light5x, light5y},
        {light6x, light6y},
        {light7x, light7y},
        {light8x, light8y},
        {light9x, light9y},
        {light10x, light10y},
        {light11x, light11y},
        {light12x, light12y},
        {light13x, light13y},
        {light14x, light14y},
        {light15x, light15y},
        {light16x, light16y},
        {light17x, light17y},
        {light18x, light18y},
        {light19x, light19y}
    };

};
#endif
