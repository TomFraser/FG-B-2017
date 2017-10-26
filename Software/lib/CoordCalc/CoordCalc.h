// UNLESS YOU ARE AL DO NOT TOUCH OR I WILL END YOU SLOWLY AND
// PAINFULLY BY MAKING YOU DO THE MERGE

#ifndef CoordCalc_h
#define CoordCalc_h

#include <Config.h>
#include <Pins.h>
#include <Defines.h>
#include <Arduino.h>
#include <Common.h>

class CoordiCalc{

public:
    CoordCalc();


    void update(int goalArea, int goalAngle);

private:
  int calcDistance(int goalArea);

  //value to store our current x
  int xCoord;

  //value to store our current y
  int yCoord;


};
#endif
