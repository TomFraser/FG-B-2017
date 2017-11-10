#include <Goalie.h>

bool Goalie::init(){
    delay(10);
}

void Goalie::calcTarget(int currentX, int currentY, int ballData) {
  xTarget = currentX + (((ballData+180)%360)-180) * X_MULTIPLIER;
  if (xTarget > 60) xTarget = 60;
  if (xTarget < -60) xTarget = -60;
  yTarget = -60;
}

int getX() {
  return xTarget;
}

int getY() {
  return yTarget;
}
