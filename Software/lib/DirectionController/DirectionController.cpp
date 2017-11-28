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

int DirectionController::getX(){
  return currX;
}

int DirectionController::getY(){
  return currY;
}

void DirectionController::updateGameData(double ballAngle_, double lightAngle_, double compassAngle_){
  ballAngle = ballAngle_;
  lightAngle = lightAngle_;
  compassAngle = compassAngle_;
}

void DirectionController::updateGoalData(int areaA_, int angleA_, int areaD_, int angleD_){
  areaA = areaA_;
  angleA = angleA_;
  areaD = areaD_;
  angleD = angleD_;

  updateCoordinates();
}

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
    #else
      pidOutput = (int) (distance * (distance < DISTANCE_CUTOFF ? CUTOFF_SPEED_SCALE : COORD_SPEED_SCALE));
    #endif
    coordSpeed = pidOutput;
  }

  // make sure our great overlord the light tracker is happy
  lightTracker.update(lightAngle, coordDirection, pidOutput, false, compassAngle);
  direction = lightTracker.getDirection();
  speed = lightTracker.getSpeed();

}

void DirectionController::calulateAttack(){
  // if got ball -> plug into light
  if(ballAngle != 65506){
    lightTracker.update(lightAngle, ballAngle, 0, true, compassAngle);
    direction = lightTracker.getDirection();
    speed = lightTracker.getSpeed();
  }
  else{
    // cant see ball -> go to predefined pos
    goToCoords(TARGET_X, TARGET_Y);
  }
}
