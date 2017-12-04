// UNLESS YOU ARE AL DO NOT TOUCH OR I WILL END YOU SLOWLY AND
// PAINFULLY BY MAKING YOU DO THE MERGE

#include <DirectionController.h>

DirectionController::DirectionController(){
  // setup PID
  pid.SetMode(AUTOMATIC);
  pid.SetOutputLimits(0, 100); // speed is 0-100
  pid.SetSampleTime(25); //CHECK IF I NEED TO SET THIS TO SMALLER THAN 200mS
}

double DirectionController::getDirection(){
  return direction;
}

int DirectionController::getSpeed(){
  return speed;
}

bool DirectionController::getFollowingBall(){
  return followingBall;
}

int DirectionController::getX(){
  return currX;
}

int DirectionController::getY(){
  return currY;
}

double DirectionController::relToAbs(double relativeDirection){
  return relativeDirection != 65506 ? doubleMod(relativeDirection - compassAngle, 360.0) : 65506;
}

double DirectionController::absToRel(double absoulteDirection){
  return absoulteDirection != 65506 ? doubleMod(absoulteDirection + compassAngle, 360.0) : 65506;
}

void DirectionController::updateGameData(double ballAngle_, double rawBallAngle_, int ballStrength_, double lightAngle_, int numSensors_, double compassAngle_){
  compassAngle = compassAngle_;
  ballStrength = ballStrength_;
  numSensors = numSensors_;

  ballAngle = relToAbs(ballAngle_);
  rawBallAngle = relToAbs(rawBallAngle_);
  lightAngle = relToAbs(lightAngle_);

  followingBall = false;
}

void DirectionController::updateGoalData(int areaA_, int angleA_, int areaD_, int angleD_){
  areaA = areaA_;
  angleA = angleA_;
  areaD = areaD_;
  angleD = angleD_;

  updateCoordinates();
}

void DirectionController::updateOtherData(int otherBallX_, int otherBallY_, int otherRobotX_, int otherRobotY_, bool otherCanSeeBall_, bool otherKnowsOwnCoords_){
  otherBallX = otherBallX_;
  otherBallY = otherBallY_;

  otherRobotX = otherRobotX_;
  otherRobotY = otherRobotY_;

  otherCanSeeBall = otherCanSeeBall_;
  otherKnowsOwnCoords = otherKnowsOwnCoords_;
}

// ------------------------ Ball stuff -----------------------------------

int DirectionController::calcBallDist(){
  // gotta figure out an algorithm for this
  return 1/ballStrength;
}

bool DirectionController::calculateBallCoordinates(){ //returns if can calulate ball coords
  if(rawBallAngle != 65506 && currX != 65506 && currY != 65506){
    int ballDist = calcBallDist();
    calcBallX = currX + ballDist*sin(angToRad*rawBallAngle);
    calcBallY = currY + ballDist*cos(angToRad*rawBallAngle);
    return true;
  }
  else{
    calcBallX = 65506;
    calcBallY = 65506;
    return false;
  }
}

int DirectionController::getBallX(){
  return calcBallX;
}

int DirectionController::getBallY(){
  return calcBallY;
}

// -----------------------------------------------------------------------------------

void DirectionController::updateCoordinates(){
  if(coordCalc.update(areaA, angleA, areaD, angleD, compassAngle)){ // returns false if cant see any goal
    currX = coordCalc.getX();
    currY = coordCalc.getY();
  }
  else{
    currX = 65506;
    currY = 65506;
  }
}

void DirectionController::goToCoords(int targetX, int targetY){
  double coordDirection;
  double coordSpeed;
  // if coordinates = 65506, cant see goal and cant figure out where we are -> stop
  if(currX == 65506 || currY == 65506){
    coordDirection = 65506;
    coordSpeed = 0;
  }
  else{
    // all good -> go for it
    // we know where we are, gotta figure out how to where we wanna be
    int deltaX = targetX - currX;
    int deltaY = targetY - currY;
    int distance = (int)sqrt((deltaX*deltaX) + (deltaY*deltaY));
    // distance = distance < DISTANCE_CUTOFF ? 0 : distance;

    coordDirection = atan2(deltaX, deltaY) * radToAng; // coords -180 to 180 on North
    // convert to 0-360
    coordDirection = coordDirection < 0 ? coordDirection + 360 : coordDirection;


    #if ENABLE_PID
      pidInput = distance;
      // Serial.print(pidInput); Serial.print(" ");
      pid.Compute();
      // Serial.println(pidOutput);
      coordSpeed = pidOutput;
    #else
      coordSpeed = (int) (distance * (distance < DISTANCE_CUTOFF ? CUTOFF_SPEED_SCALE : COORD_SPEED_SCALE));
    #endif
  }

  // make sure our great overlord the light tracker is happy
  lightTracker.update(lightAngle, coordDirection, coordSpeed, rawBallAngle, numSensors);
  direction = absToRel(lightTracker.getDirection());
  speed = lightTracker.getSpeed();

}

void DirectionController::calulateAttack(){
  // if got ball -> plug into light
  if(ballAngle != 65506){
    lightTracker.update(lightAngle, ballAngle, SPEED_VAL, rawBallAngle, numSensors);
    direction = absToRel(lightTracker.getDirection());
    speed = lightTracker.getSpeed();
    followingBall = lightTracker.getNormalGameplay();
  }
  else{
    // cant see ball -> go to predefined pos
    goToCoords(TARGET_X, TARGET_Y);
  }
}
