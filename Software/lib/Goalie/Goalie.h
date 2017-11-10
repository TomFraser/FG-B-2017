//This libraries job is to play the defender role for P2_bot (Maybe, concept codes)
#include <Arduino.h>
#include <Config.h>
#include <Pins.h>
#include <Defines.h>

#include <math.h>
#include <Vector3D.h>

class Goalie{
public:
    bool init();
    void calcTarget(int currentX, int currentY, int ballData);
    int getX();
    int getY();
private:
  int xTarget;
  int yTarget;
};
