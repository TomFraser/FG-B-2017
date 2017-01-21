#include <Light_new.h>

void Light::setThreshold(){
    for(int i = 0; i < LIGHTSENSOR_NUM; i++){
        calibrationReading[i] = analogRead(lightSensors[i]);
    }
}

void Light::read(){
    for(int i = 0; i < LIGHTSENSOR_NUM; i++){
        if(analogRead(lightSensors[i]) >= calibrationReading[i] + LIGHTSENSOR_THRESHOLD){
            lightReadings[i] = true;
        }
        else{
            lightReadings[i] = false;
        }
    }
}

void Light::sort(){
    if((int)(lightReadings[0] + lightReadings[1] + lightReadings[2] + lightReadings[3] + lightReadings[4] + lightReadings[5] + lightReadings[6] + lightReadings[7] + lightReadings[8] + lightReadings[9] + lightReadings[10] + lightReadings[11] + lightReadings[12] + lightReadings[13] + lightReadings[14] + lightReadings[15] + lightReadings[16] + lightReadings[17] + lightReadings[18] + lightReadings[19]) == 0){
        currLocation = field; //No lightsensors triggered
    }
    else{ //some light sensors are triggered
        lineLocation linePos = finalizeLine(averageSensors(lightReadings));
        getRobotLocation();
        adjust();
    }
}

lineDir Light::averageSensors(int array){
    for(int i = 0; i < LIGHTSENSOR_NUM; i++){
        if(array[i]){
            angle = angle + i*18;
            sensorCounter++;
        }
    }
    avgAngle = angle/sensorCounter + 90; //add 90 degrees
    angle = sensorCounter = 0; //reset these values for the next loop

    //strength
    double finalStrength = 1 - Math.round(avgAngle/90) > avgAngle/90 ? Math.round(avgAngle/90) - avgAngle/90 : avgAngle/90 - Math.round(avgAngle/90);
    lineDir values = {
        finalStrength,
        avgAngle
    };
    return values;
}

lineLocation Light::finalizeLine(lineDir line){
    //0-122, 90-122, 180-122, 270-122
    difference[0] = 0 - line.avgAngle;
    difference[1] = 90 - line.avgAngle;
    difference[2] = 180 - line.avgAngle;
    difference[3] = 270 - line.avgAngle;
    for(int i = 0; i < 4; i++){
        if(difference[i] < currentLow){
            currentLow = difference[i];
            chosenSide = i;
        }
    }
    lineLocation location = locations[chosenSide];
    return location;
}

void Light::getRobotLocation(lineLocation lightLine){
    prevLocation = currLocation;
  if(lightLine == small_top){
    currLocation = online_top;
  }
  else if(lightLine == small_right){
    currLocation = online_right;
  }
  else if(lightLine == small_back){
    currLocation = online_back;
  }
  else if(lightLine == small_left){
    currLocation = online_left;
  }
}

void Light::adjust(){
    if(currLocation == online_top){ //Line is unter top half of the robot                                                                           ////Out on bottom
        if(prevLocation == online_back){ //If the previous location is the back then the robot has gone over the line.
            //know to move back in until current location is online_back again.
            locr = overline_back;
        }
        else if(prevLocation == online_top){ //Robot position has remained the same, somewhat on the line.
            //Move back slowly, not to hard, still track the ball without fully going ham back across the line
            locr = online_top;
        }
    }
    else if(currLocation == online_right){ //Line is under right side of the robot                                                                  ////Out on left
        if(prevLocation == online_left){ //Line was under left side of the robot meaning its gone over the line
            //move back until currLocation = online_right left again
            locr = overline_left;
        }
        else if(prevLocation == online_right){
            //move back slowly, not to hard still track the ball maybe? The robot has remained on the line for a while for this to happen.
            locr = online_right;
        }
    }
    else if(currLocation == online_back){                                                                                                           ////out on top
        if(prevLocation == online_top){
            //Going over the line!!! FUCK! <--- DELETE THAT!
            locr = overline_top;
        }
        else if(prevLocation == online_back){
            //Remained on the line so meh!
            locr = overline_back;
        }
    }
    else if(currLocation == online_left){                                                                                                           ////Out on right
        if(currLocation == online_right){
            //Moved over the line (move bak until you see online_right again)
            locr = overline_right;
        }
        else if(currLocation == online_left){
            //remained on the line.
            locr = online_left;
        }
    }
}
