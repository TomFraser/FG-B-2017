// UNLESS YOU ARE AL DO NOT TOUCH OR I WILL END YOU SLOWLY AND
// PAINFULLY BY MAKING YOU DO THE MERGE

// TODO: need to write a thing to deal with it spazzing out at the sides

#include <SonarCoordCalc.h>

SonarCoordCalc::SonarCoordCalc(){
  // init
}

bool SonarCoordCalc::update(int sonarFront, int sonarBack, int sonarLeft, int sonarRight, double compassAngle){
  // returns the success of the coord calc
  // if true then can use the get coords functions
  // if false then have to do something else

  // horizontal (x)
  int sumX = sonarLeft + sonarRight + ROBOT_WIDTH;
  Serial.print(sonarLeft); Serial.print(" | "); Serial.print(sonarRight); Serial.print(" | "); Serial.println(sumX);
  if(SUM_X_MIN < sumX && sumX < SUM_X_MAX){
    // we somewhat checkout, lets go for it
    // use the smaller value (easily swapped)
    if(sonarLeft < sonarRight){
      xCoord = FRONT_LEFT_X + sonarLeft;
    }
    else{
      xCoord = FRONT_RIGHT_X - sonarRight;
    }
  }
  else{
    return false;
  }

  // vertical (y)
  yCoord = TARGET_Y;
  // int sumY = sonarFront + sonarRight + ROBOT_WIDTH;
  // if(SUM_Y_MIN < sumY && sumY < SUM_Y_MAX){
  //   // we somewhat checkout, lets go for it
  //   // use the smaller value (easily swapped)
  //   if(sonarFront < sonarBack){
  //     yCoord = FRONT_LEFT_Y - sonarFront;
  //   }
  //   else{
  //     yCoord = BACK_LEFT_Y + sonarBack;
  //   }
  // }
  // else{
  //   return false;
  // }

  return true;

}

int SonarCoordCalc::getX(){
  return xCoord;
}

int SonarCoordCalc::getY(){
  return yCoord;
}
