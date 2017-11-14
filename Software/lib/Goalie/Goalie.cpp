#include <Goalie.h>
// need to deal with 65506 x, y

// this library needs to:
// take in current x, y coords and raw ball angle
// and return x, y coords to go to

Goalie::Goalie(){
  // yeet
}

void Goalie::calcTarget(int currentX, int currentY, int ballData, int goalAngle, int _compass) {
  if (ballData != 65506){
      correctedAngle = (((ballData+180)%360)-180);
      lastBallData = correctedAngle;
  } else if (lastBallData == 65506){
      correctedAngle = 65506;
      lastBallData = 65506;
  } else{
      correctedAngle = lastBallData;
      lastBallData = 65506;
  }

  correctedAngle = abs(correctedAngle) < 120 ? correctedAngle : 65506;

  if(correctedAngle == 65506){
    xTarget = 0;
    yTarget = -50;
  } else{
    xTarget = currentX + correctedAngle * X_MULTIPLIER;
    if (xTarget > xRange) xTarget = xRange;
    if (xTarget < -xRange) xTarget = -xRange;

    yTarget = -50;
  }
  if (goalAngle == 65506 || goalAngle == 0)
  {
      _defendGoalAngle = _compass + 180;
  } else{
      _defendGoalAngle = goalAngle;
  }
  if (ballData == 65506) _defendGoalAngle = _compass + 180;
}

int Goalie::getX() {
  return xTarget;
}

int Goalie::getY() {
  return yTarget;
}

int Goalie::getGoalAngle(){
    return (_defendGoalAngle-180)*3;
}
