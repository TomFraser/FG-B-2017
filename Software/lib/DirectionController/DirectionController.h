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
#include <PID.h>


class DirectionController{

public:
  DirectionController();
  double getDirection();
  int getSpeed();
  int getX();
  int getY();
  void updateGameData(double ballAngle_, double rawBallAngle_, int ballStrength_, double lightAngle_, int numSensors_, double compassAngle_);
  void updateGoalData(int areaA_, int angleA_, int areaD_, int angleD_);
  void updateOtherData(int otherBallX_, int otherBallY_, int otherRobotX_, int otherRobotY_);
  bool calculateBallCoordinates();
  int getBallX();
  int getBallY();
  void goToCoords(int targetX, int targetY);
  void calulateAttack();

private:
  void updateCoordinates();

  int calcBallDist();

  double relToAbs(double relativeDirection);
  double absToRel(double absoulteDirection);

  int speed;
  double direction;

  // game data
  double ballAngle;
  double rawBallAngle;
  int ballStrength;
  double lightAngle;
  int numSensors;
  double compassAngle;

  // coordinate data
  int otherBallX;
  int otherBallY;
  int otherRobotX;
  int otherRobotY;

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

  // balls calulated coordinates
  int calcBallX;
  int calcBallY;

  // light tracker object
  LightTracker lightTracker = LightTracker();

  // CoordCalc object
  CoordCalc coordCalc = CoordCalc();

  // PID stuff
  double pidSetpoint;
  double pidInput;
  double pidOutput;

  PID pid = PID(&pidInput, &pidOutput, &pidSetpoint, PID_P, PID_I, PID_D, REVERSE);
};
#endif
