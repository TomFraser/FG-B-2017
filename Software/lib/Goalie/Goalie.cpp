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
    yTarget = GOALIE_Y;
  } else{
    xTarget = currentX + correctedAngle * X_MULTIPLIER;
    if (xTarget > GOALIE_X_RANGE) xTarget = GOALIE_X_RANGE;
    if (xTarget < -GOALIE_X_RANGE) xTarget = -GOALIE_X_RANGE;

    yTarget = GOALIE_Y;
  }
  if (goalAngle == 65506 || goalAngle == 180 || correctedAngle == 65506 || ballAngle == 65506)
  {
      _defendGoalAngle = _compass;
  } else{
      _defendGoalAngle = (goalAngle-180)*3;
  }
  if (ballData == 65506) _defendGoalAngle = _compass;
}

int Goalie::getX() {
  return xTarget;
}

int Goalie::getY() {
  return yTarget;
}

int Goalie::getGoalAngle(){
  return _defendGoalAngle;
}
