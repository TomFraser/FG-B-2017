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
        currLocation = regular;
    }
}
