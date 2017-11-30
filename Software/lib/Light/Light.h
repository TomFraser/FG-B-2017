#ifndef Light_h
#define Light_h

#include <Config.h>
#include <Common.h>
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

    //Dump On White Values
    void getOnWhite(bool *);

    //Read the light sensors
    void readLight();

    //Get current angle to avoid line
    double getAngle();

    // get if theres an error (if a sensor has bricked)
    bool getError();

private:
    // Function Definitions

    //Identify clusters of lightsensors seeing the Line
    void singleCluster(cluster *, int, int);

    //Find all the clusters
    void findClusters(cluster *);


    // cluster shit
    double getClusterAngle(int clusterBegin, int clusterEnd);

    // Other Stuff

    //init stuff
    #if AUTO_LIGHT
      int thresholds[LIGHTSENSOR_NUM];
    #else
      #if ROBOT
        //o_bot
        int thresholds[LIGHTSENSOR_NUM] = {1000, 1000, 1000, 1000, 900, 1000, 1000, 1000, 1000, 900, -1, 1000, 1000, 1000, 1000, 1000, 1000, 1000, -1};
      #else
        //p2_bot
        int thresholds[LIGHTSENSOR_NUM] = {189, 257, 355, 247, 275, 339, 346, 230, 305, 314, 169, 176, 180, 211, 327, 477, 323, 338, 322, 252};
      #endif
    #endif

    int lightSensors[LIGHTSENSOR_NUM];

    bool error = false;

    //for reading light
    int detectedNumber;

    // bool seeingWhite[LIGHTSENSOR_NUM] = {true, true, true, true, true, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false};
    bool seeingWhite[LIGHTSENSOR_NUM];

    //cluster stuff
    double lightCoords[20][2] = {
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
        {light19x, light19y},
        {light20x, light20y}
    };

    //For angle countback and filtering
    double countback[NUM_COUNTBACK];
};
#endif
