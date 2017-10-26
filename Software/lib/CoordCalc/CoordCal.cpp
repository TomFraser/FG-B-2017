// UNLESS YOU ARE AL DO NOT TOUCH OR I WILL END YOU SLOWLY AND
// PAINFULLY BY MAKING YOU DO THE MERGE

#include <CoordCalc.h>

CoordCalc::CoordCalc(){
  // init
}

int CoordCalc::calcDistance(int goalArea, int goalAngle){
  //do some hectic maths stuff
  return 20; //cm //#lol #hardcodelyf
}

void CoordCalc::update(int areaA, int angleA, int areaD, int angleD){
  //-30 is the 'no goal' angle

  bool attackGoal = (angleA != -30)
  bool defenseGoal = (angleD != -30)

  int distance = calcDistance();


  // attack calulations
  int xAttack;
  int yAttack;

  if(attackGoal){
    int xGoal = distance*sin(angleToRad*angleA);
    int yGoal = distance*cos(angleToRad*angleA);

    xAttack = ATTACK_GOAL_X-xGoal;
  }

  // defense calulations
  

}

int CoordCalc::getX(){
  return xCoord;
}

int CoordCalc::getY(){
  return yCoord;
}
