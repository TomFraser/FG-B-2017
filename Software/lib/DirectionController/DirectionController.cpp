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
}

void DirectionController::setTarget(int x, int y){
  targetX = x;
  targetY = y;
}

void DirectionController::calulate(){
  // if got ball -> plug into light
  if(ballAngle != 65506){
    lightTracker.update(lightAngle, ballAngle, 0, true, compassAngle);
    direction = lightTracker.getDirection();
    speed = lightTracker.getSpeed();
  }
  else{
    // cant see ball, need to figure out where we are
    if(coordCalc.update(areaA, angleA, areaD, angleD, compassAngle)){ // returns false if cant see any goal
      currX = coordCalc.getX();
      currY = coordCalc.getY();

      // Serial.print("X: "); Serial.print(currX); Serial.print(" Y: "); Serial.println(currY);

      // now we know where we are, gotta figure out how to where we wanna be
      int deltaX = targetX - currX;
      int deltaY = targetY - currY;
      int distance = (int)sqrt((deltaX*deltaX) + (deltaY*deltaY));
      // distance = distance < DISTANCE_CUTOFF ? 0 : distance;

      double coordDirection = atan2(deltaX, deltaY) * radToAng; // coords -180 to 180 on North
      // convert to 0-360
      coordDirection = coordDirection < 0 ? coordDirection + 360 : coordDirection;

      int coordSpeed = (int) (distance * (distance < DISTANCE_CUTOFF ? CUTOFF_SPEED_SCALE : COORD_SPEED_SCALE));

      // Serial.print("Dir: "); Serial.println(coordDirection);
      // Serial.print("Speed: "); Serial.println(coordSpeed);

      direction = coordDirection;
      speed = coordSpeed;

      // Serial.print("CoordDir: "); Serial.print(coordDirection); Serial.print(" CoordSpeed: "); Serial.println(coordSpeed);

      // make sure our great overlord the light tracker is happy
      lightTracker.update(lightAngle, coordDirection, coordSpeed, false, compassAngle);
      direction = lightTracker.getDirection();
      speed = lightTracker.getSpeed();


      // Serial.println(direction);
      // Serial.println(speed);
    }
    else{
      // coords didnt work out, just chill here till we ok again
      speed = 0;
      direction = 0;

      
    }
  }

}
