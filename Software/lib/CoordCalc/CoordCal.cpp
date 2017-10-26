// UNLESS YOU ARE AL DO NOT TOUCH OR I WILL END YOU SLOWLY AND
// PAINFULLY BY MAKING YOU DO THE MERGE

#include <CoordCalc.h>

CoordCalc::CoordCalc(){
  // init
}

int CoordCalc::calcDistance(int goalArea, int goalAngle){
  return 0.03*goalArea^2 - 4.36*goalArea + 163.61
}

bool CoordCalc::update(int areaA, int angleA, int areaD, int angleD){
  // returns the success of the coord calc
  // if true then can use the get coords functions
  // if false then have to do something else


  //-30 is the 'no goal' angle
  bool attackGoal = (angleA != -30)
  bool defenseGoal = (angleD != -30)

  // attack calulations
  if(attackGoal){
    int distance = calcDistance(areaA, angleA);

    int xGoal = distance*sin(angleToRad*angleA);
    int yGoal = distance*cos(angleToRad*angleA);

    xAttack = ATTACK_GOAL_X-xGoal;
    yAttack = ATTACK_GOAL_Y-yGoal;
  }

  // defense calulations
  if(defenseGoal){
    int distance = calcDistance(areaD, angleD);

    int xGoal = distance*sin(angleToRad*angleD);
    int yGoal = distance*cos(angleToRad*angleD);

    xDefense = DEFENSE_GOAL_X-xGoal;
    yDefense = DEFENSE_GOAL_Y-yGoal;
  }

  if(attackGoal && defenseGoal){
    // we can see both goals
    // so yeah, idk what were gonna do here maybe average
    // what happens when one memes tho? we cant really tell which
    // one is correct and the other is a meme

    // just gonna average for now
    xCoord = (int)round((xAttack + xDefense)/2)
    yCoord = (int)round((yAttack + yDefense)/2)
  }
  else if(attackGoal){
    // only attack goal can be seen
    xCoord = xAttack;
    yCoord = yAttack;
  }
  else if(defenseGoal){
    // only defenseGoal can be seen
    xCoord = xDefense;
    yCoord = yDefense;
  }
  else{
    // no goals
    return false;
  }

  // make sure our coords are within the field
  return (FRONT_LEFT_X < xCoord && xCoord < FRONT_RIGHT_X) && (FRONT_LEFT_Y < yCoord && yCoord < BACK_LEFT_Y)



}

int CoordCalc::getX(){
  return xCoord;
}

int CoordCalc::getY(){
  return yCoord;
}
