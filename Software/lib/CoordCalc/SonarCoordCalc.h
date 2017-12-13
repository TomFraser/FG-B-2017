// UNLESS YOU ARE AL DO NOT TOUCH OR I WILL END YOU SLOWLY AND
// PAINFULLY BY MAKING YOU DO THE MERGE

#ifndef SonarCoordCalc_h
#define SonarCoordCalc_h

#include <Config.h>
#include <Pins.h>
#include <Defines.h>
#include <Arduino.h>
#include <Common.h>

class SonarCoordCalc{

public:
    SonarCoordCalc();


    bool update(int sonarFront, int sonarBack, int sonarLeft, int sonarRight, double compassAngle);

    int getX();
    int getY();

private:

  //value to store our current x
  int xCoord;

  //value to store our current y
  int yCoord;

  //value to store current attack x
  int xAttack;

  //value to store current attack y
  int yAttack;

  //value to store current defense x
  int xDefense;

  //value to store current defense y
  int yDefense;
};
#endif
