// UNLESS YOU ARE AL DO NOT TOUCH OR I WILL END YOU SLOWLY AND
// PAINFULLY BY MAKING YOU DO THE MERGE

#include <DirectionController.h>

DirectionController::DirectionController(){
  // init
}

double DirectionController::getDirection(){
  return direction;
}

int DirectionController::getSpeed(){
  return speed;
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
}

void DirectionController::calulate(){
  // if got ball -> plug into light
  if(ballAngle != 65506){
    lightTracker.update(lightAngle, ballAngle, true, compassAngle);
    direction = lightTracker.getDirection();
    speed = lightTracker.speed();
  }
  else{
    // cant see ball, need to figure out where we are
    coordCalc.update(areaA, angleA, areaD, angleD); // can check the response of this but ceebs
    int currX = coordCalc.getX();
    int currY = coordCalc.getY();

    // now we know where we are, gotta figure out how to where we wanna be
    int deltaX = TARGET_X - currX;
    int deltaY = TARGET_Y - currY;
    int distance = (int)sqrt((deltaX*deltaX) + (deltaY*deltaY));
    distance = distance < DISTANCE_CUTOFF ? 0 : distance;

    double coordDirection = atan2(deltaY, deltaX) * radToAng;
    int coordSpeed = (int) (distance*COORD_SPEED_SCALE);

    // make sure our great overlord the light tracker is happy
    lightTracker.update(lightAngle, coordDirection, coordSpeed, false, compassAngle);
    direction = lightTracker.getDirection();
    speed = lightTracker.getSpeed();
  }

}
