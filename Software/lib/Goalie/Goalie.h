//This libraries job is to play the defender role for P2_bot (Maybe, concept codes)
#include <Arduino.h>
#include <Config.h>
#include <Pins.h>
#include <Defines.h>
#include <Common.h>

#include <math.h>
#include <Vector3D.h>

class Goalie{
public:
    Goalie();
    void calcTarget(int currentX, int currentY, int ballData, int goalAngle, double _rotation, double _compass);
    int getX();
    int getY();
    int getGoalAngle();
private:
  int xTarget;
  int yTarget;
  int _defendGoalAngle;
  int correctedAngle;
  int lastBallData;

  int xRange = 35;
};
