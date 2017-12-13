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
  bool getFollowingBall();
  int getX();
  int getY();
  void updateGameData(double ballAngle_, double rawBallAngle_, int ballStrength_, double lightAngle_, int numSensors_, double compassAngle_, bool isGoalie_);
  void updateGoalData(int areaA_, int angleA_, int areaD_, int angleD_);
  void updateOtherData(int otherBallX_, int otherBallY_, int otherRobotX_, int otherRobotY_, bool otherCanSeeBall_, bool otherKnowsOwnCoords_);
  int getBallX();
  int getBallY();
  double getBallAngle();
  void goToCoords(int targetX, int targetY);
  void calculateAttack();
  void calculateGoalie();


private:
  void updateGoalCoordinates();
  void updateBallCoordinates();


  int calcBallDist();

  double relToAbs(double relativeDirection);
  double absToRel(double absoulteDirection);

  int getAllBallX();
  int getAllBallY();

  int speed;
  double direction;

  // game data
  double ballAngle;
  double rawBallAngle;
  int ballStrength;
  double lightAngle;
  int numSensors;
  double compassAngle;
  bool isGoalie;

  // coordinate data
  int otherBallX;
  int otherBallY;
  int otherRobotX;
  int otherRobotY;
  bool otherCanSeeBall;
  bool otherKnowsOwnCoords;

  // sonar data
  int rangeFront;
  int rangeBack;
  int rangeLeft;
  int rangeRight;

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
  int ballX;
  int ballY;

  // if we are following ball
  bool followingBall;

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
