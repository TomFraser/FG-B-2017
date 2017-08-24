#include <Light.h>

Light::Light(){
    //init
    pinMode(LIGHT_1, INPUT);
    pinMode(LIGHT_2, INPUT);
    pinMode(LIGHT_3, INPUT);
    pinMode(LIGHT_4, INPUT);
    pinMode(LIGHT_5, INPUT);
    pinMode(LIGHT_6, INPUT);
    pinMode(LIGHT_7, INPUT);
    pinMode(LIGHT_8, INPUT);
    pinMode(LIGHT_9, INPUT);
    pinMode(LIGHT_10, INPUT);
    pinMode(LIGHT_11, INPUT);
    pinMode(LIGHT_12, INPUT);
    pinMode(LIGHT_13, INPUT);
    pinMode(LIGHT_14, INPUT);
    pinMode(LIGHT_15, INPUT);
    pinMode(LIGHT_16, INPUT);
    pinMode(LIGHT_17, INPUT);
    pinMode(LIGHT_18, INPUT);
    pinMode(LIGHT_19, INPUT);

    lightSensors[0] = LIGHT_7;
    lightSensors[1] = LIGHT_6;
    lightSensors[2] = LIGHT_5;
    lightSensors[3] = LIGHT_4;
    lightSensors[4] = LIGHT_3;
    lightSensors[5] = LIGHT_2;
    lightSensors[6] = LIGHT_1;
    lightSensors[7] = LIGHT_19;
    lightSensors[8] = LIGHT_18;
    lightSensors[9] = LIGHT_17;
    lightSensors[10] = LIGHT_16;
    lightSensors[11] = LIGHT_15;
    lightSensors[12] = LIGHT_14;
    lightSensors[13] = LIGHT_13;
    lightSensors[14] = LIGHT_12;
    lightSensors[15] = LIGHT_11;
    lightSensors[16] = LIGHT_10;
    lightSensors[17] = LIGHT_9;
    lightSensors[18] = LIGHT_8;

    for(int i = 0; i < NUM_COUNTBACK; i++){
      countback[i] = -1;
    }

}


//====================Getter Dump Functions===========================
void Light::getVals(int *vals){
  for(int i = 0; i < LIGHTSENSOR_NUM; i++){
      // Serial.println(analogRead(lightSensors[i]));
      vals[i] = analogRead(lightSensors[i]);
  }
}

void Light::getOnWhite(bool *vals){
  for(int i=0; i < LIGHTSENSOR_NUM; i++){
    vals[i] = seeingWhite[i];
  }
}

//=============================Other Functions=====================
void Light::init(){
    for(int i = 0; i < LIGHTSENSOR_NUM; i++){
        thresholds[i] = 0;
    }

    for(int n = 0; n < LIGHTSENSOR_AVG; n++){
        for(int i = 0; i < LIGHTSENSOR_NUM; i++){
          thresholds[i] += analogRead(lightSensors[i]);
        }
    }

    for(int i = 0; i < LIGHTSENSOR_NUM; i++){
        thresholds[i] /= LIGHTSENSOR_AVG;
        thresholds[i] += LIGHTSENSOR_THRESHOLD;
    }
}

void Light::readLight(){
    detectedNumber = 0;
    for(int i = 0; i < LIGHTSENSOR_NUM; i++){
        if(analogRead(lightSensors[i]) >= thresholds[i]){
            seeingWhite[i] = true;
            detectedNumber++;
        }
        else{
            seeingWhite[i] = false;
        }
    }
}

//[0, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0]
void Light::singleCluster(cluster *returnClus, int startNum, int begin){
  if(seeingWhite[startNum%LIGHTSENSOR_NUM]){
    if(seeingWhite[(startNum+1)%LIGHTSENSOR_NUM]){
      singleCluster(returnClus, startNum+1, begin);
    }
    else{
      returnClus->exist = true;
      returnClus->begin = begin;
      returnClus->end = startNum;
      return;
    }
  }
  else{
    returnClus->exist = false;
    return;
  }
}

//foundClusters is length of 2 (returns 2 best clusters)
void Light::findCluster(cluster *bestCluster){
  cluster foundClusters[maxNumClusters];
  cluster temp = {false, 0, 0};
  for(int i = 0; i < maxNumClusters; i++){
    foundClusters[i] = temp;
  }

  int index = 0;
  int num = 0;
  while(num < LIGHTSENSOR_NUM){
    cluster c;
    singleCluster(&c, num, num);
    if(c.exist){
      foundClusters[index] = c;
      index++;
      num = c.end+1;
    }
    else{
      num++;
    }
  }

  // print all found clusters
  // for(int i=0; i<maxNumClusters; i++){
  //   Serial.print(foundClusters[i].begin); Serial.print(" "); Serial.print(foundClusters[i].end); Serial.print(" | ");
  // }
  // Serial.println();


  //now find the largest cluster
  int firstIndex = 0;
  int maxSize = 0;

  // for(int i=0; i<maxNumClusters; i++){
  //   Serial.print(foundClusters[i].exist); Serial.print(" | ");
  // }
  // Serial.println();

  // Check if we found any clusters at all
  if(foundClusters[0].exist){
    for(int i=0; i<maxNumClusters; i++){
      cluster cluster = foundClusters[i];
      if(cluster.exist){
        int size = cluster.end - cluster.begin + 1;
        if(size > maxSize){
          maxSize = size;
          firstIndex = i;
        }
      }
    }

    //now we have them return them
    bestCluster->exist = true;
    bestCluster->begin = foundClusters[firstIndex].begin;
    bestCluster->end = foundClusters[firstIndex].end;

  }
  else {
    // If not, say so
    bestCluster->exist = false;
  }
}

double Light::getAngle(){
    readLight();

    cluster bestCluster;
    findCluster(&bestCluster);

    double directionAngle;

    if(!bestCluster.exist){
      directionAngle = -1;
    }
    else{
      double xavg = 0;
      double yavg = 0;

      for(int i=bestCluster.begin; i<=bestCluster.end; i++){
        xavg += lightCoords[i%LIGHTSENSOR_NUM][0];
        yavg += lightCoords[i%LIGHTSENSOR_NUM][1];
      }

      xavg /= bestCluster.end-bestCluster.begin + 1;
      yavg /= bestCluster.end-bestCluster.begin + 1;

      double lineAngle = -atan2(yavg, xavg)*radToAng; //0-180/-180 on east
      lineAngle += lineAngle < 0 ? 360 : 0; //lineAngle is now a 0-360 value on east
      lineAngle = fmod(lineAngle + 90, 360); //convert to 0-360 on north
      directionAngle = fmod(lineAngle + 180, 360); //make it the opposite direction
    }
    double countbackVal = directionAngle;

    // check the countback for if all the values are greater than 0 if we are greater than 0
    if(directionAngle > -1){
      bool allGood = true;
      for(int i; i < NUM_COUNTBACK; i++){
        if(countback[i] < 0){
          allGood = false;
        }
      }
      if(!allGood){
        directionAngle = -1;
      }
    }

    // for(int i=0; i<NUM_COUNTBACK; i++){
    //   Serial.print(i); Serial.print(" "); Serial.println(countback[i]);
    //   Serial.println();
    // }


    for(int i=0; i<NUM_COUNTBACK-1; i++){
      countback[i+1] = countback[i];
    }

    countback[0] = countbackVal;

    return directionAngle;
}


// int Light::identifyQuadrant(double angle){
//     // int num;
//     // if(angle >= 0 && angle <= 90){
//     //   num = 2;
//     // }
//     // else if(angle <= 180){
//     //   num = 3;
//     // }
//     // else if(angle <= 270){
//     //   num = 4;
//     // }
//     // else{
//     //   num = 1;
//     // }
//     //
//     // return num;
//     return int(angle/90) + 1;
// }

double Light::getDirection(){
  double direction = getAngle();
  double lightDir = direction;
  if(seeingLine){
    if(direction == -1){
      // just stopped seeing the line
      double diff = abs(lineInitDirection - lastLightVal);
      // Serial.print("Init: "); Serial.println(lineInitDirection);
      // Serial.print("LastLight: "); Serial.println(lastLightVal);
      // Serial.print("Diff: "); Serial.println(diff);
      // Serial.println("");
      if(!(diff > 90 && diff < 270)){
        // exited on the correct side of the line
        // Serial.println(lastLightVal);
        seeingLine = false;
        lineInitDirection = 0;
      }
      else{
        // exited on the wrong side of the line - go back the way we came
        direction = lineInitDirection;
      }
    }
    else{
      // was seeing line and still are - need to check if we're over or not
      double diff = abs(lineInitDirection - direction);
      if(diff > 45 && diff < 315){
        // we have flipped our direction so just move at initial direction
        direction = lineInitDirection;
      }
    }
  }
  else {
    if(direction != -1){
      // we just started seeing the line!
      lineInitDirection = direction;
      seeingLine = true;
    }
    // otherwise still not seeing the line - all goods
  }

  if(lightDir != -1){
    lastLightVal = lightDir;
  }

  return direction;
}
