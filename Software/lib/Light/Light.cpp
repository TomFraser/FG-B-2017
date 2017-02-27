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

}

void Light::getVals(int *vals){
  for(int i = 0; i < LIGHTSENSOR_NUM; i++){
      Serial.println(analogRead(lightSensors[i]));
  }
}

void Light::init(){
    for(int i = 0; i < LIGHTSENSOR_NUM; i++){
        thresholds[i] = analogRead(lightSensors[i] + LIGHTSENSOR_THRESHOLD);
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

cluster Light::singleCluster(int startNum, int begin){
  if(seeingWhite[startNum]){
    if(seeingWhite[startNum+1]){
      singleCluster(startNum+1, begin);
    }
    else{
      cluster lightCluster;
      lightCluster.exist = true;
      lightCluster.begin = begin;
      lightCluster.end = startNum;
      return lightCluster;
    }
  }
  else{
    cluster noCluster;
    noCluster.exist = false;
    return noCluster;
  }
}

//foundClusters is length of 2 (returns 2 best clusters)
void Light::findClusters(cluster *bestClusters){
  cluster foundClusters[maxNumClusters];
  int index = 0;
  int num = 0;
  while(num < LIGHTSENSOR_NUM){
    cluster c = singleCluster(num, num);
    if(c.exist){
      foundClusters[index] = c;
      index++;
      num = c.end;
    }
    else{
      num++;
    }
  }

  //now find the largest 2 clusters
  int firstIndex = 0;
  int secondIndex = 0;

  int maxSize = 0;
  int secondSize = 0;

  for(int i=0; i<maxNumClusters; i++){
    cluster cluster = foundClusters[i];
    int size = cluster.end - cluster.begin;
    if(size > maxSize){
      maxSize = size;
      firstIndex = i;
    }
    else if(size > secondSize){
      secondSize = size;
      secondIndex = i;
    }
  }

  //now we have them return them
  bestClusters[0] = foundClusters[firstIndex];
  bestClusters[1] = foundClusters[secondIndex];
}

double Light::getAngle(){
    cluster bestClusters[2];
    findClusters(bestClusters);
    double clus1xavg = 0;
    double clus1yavg = 0;

    for(int i=bestClusters[0].begin; i<=bestClusters[0].end; i++){
      clus1xavg += lightCoords[i][0];
      clus1yavg += lightCoords[i][1];
    }

    clus1xavg /= bestClusters[0].end-bestClusters[0].begin;
    clus1yavg /= bestClusters[0].end-bestClusters[0].begin;

    double clus2xavg = 0;
    double clus2yavg = 0;

    for(int i=bestClusters[1].begin; i<=bestClusters[1].end; i++){
      clus2xavg += lightCoords[i][0];
      clus2yavg += lightCoords[i][1];
    }

    clus2xavg /= bestClusters[1].end-bestClusters[1].begin;
    clus2yavg /= bestClusters[1].end-bestClusters[1].begin;

    double deltaX = clus2xavg - clus1xavg;
    double deltaY = clus2yavg - clus1yavg;

    double angle = atan2(deltaY, deltaX);

    return angle;

}
