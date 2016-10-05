#include <LightController.h>

LightController::LightController(){
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

void LightController::determineThresholds(){
    for(int i = 0; i < LIGHTSENSOR_NUM; i++){
        thresholds[i] = analogRead(lightSensors[i] + LIGHTSENSOR_THRESHOLD);
    }
}

void LightController::letsDoSomeGeometry(){
    //Cuck. Need to sit down with everyone and figure out how we are gonna do this.
}
