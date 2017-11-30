// UNLESS YOU ARE AL DO NOT TOUCH OR I WILL END YOU SLOWLY AND
// PAINFULLY BY MAKING YOU DO THE MERGE

// TODO: need to write a thing to deal with it spazzing out at the sides

#include <CoordCalc.h>

CoordCalc::CoordCalc(){
  // init
}

int CoordCalc::calcDistance(int goalArea, int goalAngle, bool attack){
  // int goalDiff;

  // if(attack){
  //   goalDiff = goalAngle < 180 ? goalAngle : 360 - goalAngle;
  // }
  // else{
  //   // defense so back angle
  //   goalDiff = goalAngle < 180 ? 180 - goalAngle : goalAngle - 180;
  // }
  //
  // if(goalDiff > 40){
  //   goalArea += 0.0009702068*goalDiff*goalDiff*goalDiff - 0.159890341*goalDiff*goalDiff + 8.8953257223*goalDiff - 159.3540633919;
  // }
  //
  // return -0.0004831603*goalArea*goalArea*goalArea + 0.0745118988*goalArea*goalArea - 5.0391683715*goalArea + 150.2067141813;

  return 0.0050260035*exp(0.0419970726*goalArea);
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

    int distance = calcDistance(areaA, angleA, true);

    if(distance < 100 && distance > 0)
    {
      int xGoal = distance*sin(angToRad*angleA);
      int yGoal = distance*cos(angToRad*angleA);

      xAttack = ATTACK_GOAL_X-xGoal;
      yAttack = ATTACK_GOAL_Y-yGoal;
    }
    else{
      attackGoal = false;
    }

  }

  // defense calulations
  if(defenseGoal){
    angleD = mod(angleD - compassAngle, 360); // CHECK THIS

    int distance = calcDistance(areaD, angleD, false);

    if(distance < 100 && distance > 0)
    {
      int xGoal = distance*sin(angToRad*angleD);
      int yGoal = distance*cos(angToRad*angleD);

      xDefense = DEFENSE_GOAL_X-xGoal;
      yDefense = DEFENSE_GOAL_Y-yGoal;
    }
    else{
      defenseGoal = false;
    }
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
