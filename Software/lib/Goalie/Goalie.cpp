#include <Goalie.h>
// need to deal with 65506 x, y

// this library needs to:
// take in current x, y coords and raw ball angle
// and return x, y coords to go to

Goalie::Goalie(){
  // yeet
}

void Goalie::calcTarget(int currentX, int currentY, int ballData) {
  if(ballData == 65506){
    xTarget = 0;
    yTarget = -70;
  }
  else{
    xTarget = currentX + (((ballData+180)%360)-180) * X_MULTIPLIER;
    if (xTarget > 30) xTarget = 30;
    if (xTarget < -30) xTarget = -30;

    yTarget = -70;
  }
}

int Goalie::getX() {
  return xTarget;
}

int Goalie::getY() {
  return yTarget;
}
