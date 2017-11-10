// UNLESS YOU ARE AL DO NOT TOUCH OR I WILL END YOU SLOWLY AND
// PAINFULLY BY MAKING YOU DO THE MERGE

#include <CoordCalc.h>

CoordCalc::CoordCalc(){
  // init
}

int CoordCalc::calcDistance(int goalArea, int goalAngle){
  if(goalArea < 30){
    return 0.2463157579*goalArea*goalArea - 15.1362757297*goalArea + 287.7937274186;
  }
  else{
    return 0.0247334755*goalArea*goalArea - 3.7345415778*goalArea + 144.9840085288;
  }
}

bool CoordCalc::update(int areaA, int angleA, int areaD, int angleD, double compassAngle){
  // returns the success of the coord calc
  // if true then can use the get coords functions
  // if false then have to do something else


  //-30 is the 'no goal' angle
  bool attackGoal = (angleA != 65506);
  bool defenseGoal = (angleD != 65506);

  // attack calulations
  if(attackGoal){

    angleA = mod(angleA - compassAngle, 360); // CHECK THIS

    int distance = calcDistance(areaA, angleA);

    int xGoal = distance*sin(angToRad*angleA);
    int yGoal = distance*cos(angToRad*angleA);

    xAttack = ATTACK_GOAL_X-xGoal;
    yAttack = ATTACK_GOAL_Y-yGoal;
  }

  // defense calulations
  if(defenseGoal){
    angleD = mod(angleD - compassAngle, 360); // CHECK THIS

    int distance = calcDistance(areaD, angleD);

    int xGoal = distance*sin(angToRad*angleD);
    int yGoal = distance*cos(angToRad*angleD);

    xDefense = DEFENSE_GOAL_X-xGoal;
    yDefense = DEFENSE_GOAL_Y-yGoal;
  }

  if(attackGoal && defenseGoal){
    // we can see both goals
    // so yeah, idk what were gonna do here maybe average
    // what happens when one memes tho? we cant really tell which
    // one is correct and the other is a meme

    // take the larger goal
    if(areaA > areaD){
      xCoord = xAttack;
      yCoord = yAttack;
    }
    else{
      xCoord = xDefense;
      yCoord = yDefense;
    }

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

  // make sure our coords are within the field - ceebs doing this, i dont think its good
  // return (FRONT_LEFT_X < xCoord && xCoord < FRONT_RIGHT_X) && (FRONT_LEFT_Y < yCoord && yCoord < BACK_LEFT_Y);
  return true;
}

int CoordCalc::getX(){
  return xCoord;
}

int CoordCalc::getY(){
  return yCoord;
}
