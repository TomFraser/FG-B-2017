#ifndef Light_h
#define Light_h

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

    // Other Stuff

    //init stuff
    #if ROBOT
      //o_bot
      int thresholds[19] = {112, 116, 109, 117, 100, 120, 168, 214, 171, 110, 140, 193, 191, 164, 142, 188, 183, 142, 119};
    #else
      //p2_bot
      int thresholds[19] = {133, 138, 176, 176, 115, 121, 201, 209, 157, 194, 231, 194, 176, 146, 147, 153, 208, -1, 187};
    #endif


    int lightSensors[19];

    //bricked threshold
    int brickedThreshold = 700;

    bool error = false;

    //for reading light
    int detectedNumber;

    // bool seeingWhite[19] = {true, true, true, true, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false};
    bool seeingWhite[19];

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

    //For angle countback and filtering
    double countback[NUM_COUNTBACK];
};
#endif
