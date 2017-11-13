// UNLESS YOU ARE AL DO NOT TOUCH OR I WILL END YOU SLOWLY AND
// PAINFULLY BY MAKING YOU DO THE MERGE

#ifndef DirectionController_h
#define DirectionController_h

#include <Config.h>
#include <Pins.h>
#include <Defines.h>
#include <Arduino.h>
#include <Common.h>
#include <LightTracker.h>
#include <CoordCalc.h>

class DirectionController{

public:
  DirectionController();
  double getDirection();
  int getSpeed();
  int getX();
  int getY();
  void updateGameData(double ballAngle_, double lightAngle_, double compassAngle_);
  void updateGoalData(int areaA_, int angleA_, int areaD_, int angleD_);
  void goToCoords(int targetX, int targetY);
  void calulateAttack();

private:
  void updateCoordinates();

  int speed;
  double direction;

  // game data
  double ballAngle;
  double lightAngle;
  double compassAngle;

  // goal data
  int areaA; // attack goal
  int angleA;

  int areaD; // defense goal
  int angleD;

  // target coordinates
  int targetX;
  int targetY;

  //current coords
  int currX;
  int currY;

  // light tracker object
  LightTracker lightTracker = LightTracker();

  // CoordCalc object
  CoordCalc coordCalc = CoordCalc();
};
#endif
