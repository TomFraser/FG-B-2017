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
        int thresholds[LIGHTSENSOR_NUM] = {655, 726, 560, 615, 598, 587, 606, 613, 727, 586, 445, 592, 562, 522, 394, 344, 258, 375, 431, 469};
      #else
        //p2_bot
        int thresholds[LIGHTSENSOR_NUM] = {215, 280, 332, 216, 214, 208, 197, 222, 329, 240, 178, 248, 240, 226, 298, 188, 212, 244, 247, 204};
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
