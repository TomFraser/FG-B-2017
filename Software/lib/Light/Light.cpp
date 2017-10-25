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

    lightSensors[0] = LIGHT_1;
    lightSensors[1] = LIGHT_2;
    lightSensors[2] = LIGHT_3;
    lightSensors[3] = LIGHT_4;
    lightSensors[4] = LIGHT_5;
    lightSensors[5] = LIGHT_6;
    lightSensors[6] = LIGHT_7;
    lightSensors[7] = LIGHT_8;
    lightSensors[8] = LIGHT_9;
    lightSensors[9] = LIGHT_10;
    lightSensors[10] = LIGHT_11;
    lightSensors[11] = LIGHT_12;
    lightSensors[12] = LIGHT_13;
    lightSensors[13] = LIGHT_14;
    lightSensors[14] = LIGHT_15;
    lightSensors[15] = LIGHT_16;
    lightSensors[16] = LIGHT_17;
    lightSensors[17] = LIGHT_18;
    lightSensors[18] = LIGHT_19;

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

bool Light::getError(){
  return error;
}

//=============================Other Functions=====================
void Light::init(){
    // actually does nothing lol, in here just incase i feel like doing
    // something sometime
}

void Light::readLight(){
    detectedNumber = 0;
    for(int i = 0; i < LIGHTSENSOR_NUM; i++){
      if(thresholds[i] != -1){
        int val = analogRead(lightSensors[i]);
        if(val >= thresholds[i]){
            seeingWhite[i] = true;
            detectedNumber++;
        }
        else{
            seeingWhite[i] = false;
        }
      }
      else{
        seeingWhite[i] = false;
      }
    }

    // A thing for the sensors that dont work
    #if ROBOT
      if(seeingWhite[9] && seeingWhite[11]){
        seeingWhite[10] = true;
      }
    #else
      if(seeingWhite[16] && seeingWhite[18]){
        seeingWhite[17] = true;
      }
    #endif
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

//foundClusters is a cluster array of length maxNumClusters
void Light::findClusters(cluster *foundClusters){
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

  index --; //index is now at the last index of clusters

  if(foundClusters[index].end > 18 && foundClusters[0].begin == 0){
    // // then we have a wrapped cluster so make the first cluster invalid
    foundClusters[0] = {true, -1, -1};
  }



  // print all found clusters
  // for(int i=0; i<maxNumClusters; i++){
  //   Serial.print(foundClusters[i].begin); Serial.print(" "); Serial.print(foundClusters[i].end); Serial.print(" | ");
  // }
  // Serial.println();
}

double Light::getAngle(){
    // get all the current clusters
    cluster foundClusters[maxNumClusters];
    findClusters(foundClusters);

    double directionAngle;

    if(!foundClusters[0].exist){ // if we found no clusters
      directionAngle = 65506;
    }
    else{
      double clusXavg;
      double clusYavg;

      double xavg = 0;
      double yavg = 0;

      double numClusters = 0;

      for(int i=0; i < maxNumClusters; i++){
        if(!foundClusters[i].exist){
          break;
        }

        if(foundClusters[i].begin != -1){
          numClusters ++;
          clusXavg = 0;
          clusYavg = 0;
          for(int j=foundClusters[i].begin; j<=foundClusters[i].end; j++){
            clusXavg += lightCoords[j%LIGHTSENSOR_NUM][0];
            clusYavg += lightCoords[j%LIGHTSENSOR_NUM][1];
          }

          clusXavg /= foundClusters[i].end-foundClusters[i].begin + 1;
          clusYavg /= foundClusters[i].end-foundClusters[i].begin + 1;

          xavg += clusXavg;
          yavg += clusYavg;
        }
      }

      if(numClusters > 0){
        xavg /= numClusters;
        yavg /= numClusters;

        double lineAngle = -atan2(yavg, xavg)*radToAng; //0-180/-180 on east
        lineAngle += lineAngle < 0 ? 360 : 0; //lineAngle is now a 0-360 value on east
        lineAngle = fmod(lineAngle + 90, 360); //convert to 0-360 on north
        directionAngle = fmod(lineAngle + 180, 360); //make it the opposite direction
      }
      else{
        directionAngle = 65506;
      }
    }

    double countbackVal = directionAngle;

    // check the countback for if all the values are greater than 0 if we are greater than 0
    if(directionAngle != 65506){
      bool allGood = true;
      for(int i=0; i < NUM_COUNTBACK; i++){
        if(countback[i] < 0){
          allGood = false;
        }
      }
      if(!allGood){
        directionAngle = 65506;
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
