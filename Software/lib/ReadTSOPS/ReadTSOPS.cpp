#include <ReadTSOPS.h>
#include <Arduino.h>

// #define TSOP_NUM 12
// #define MAX_READS 128
//
// #define POWER_PIN_1 0
// #define POWER_PIN_2 0
// #define READ_THRESHOLD 40

ReadTSOPS::ReadTSOPS(){
    for(int i = 0; i < TSOP_NUM; i++){
        pinMode(sensors[i], INPUT);
    }
    pinMode(POWER_PIN_1, OUTPUT);
    pinMode(POWER_PIN_2, OUTPUT);

    bestSensor = 0;
    index = 0;
}

void ReadTSOPS::read(int mode){
    bestSensor = 0;
    index = 0;

    switch(mode){
        case 0: //Nothing
            break;
        case 1: //Reading
            digitalWrite(POWER_PIN_1, HIGH);
            digitalWrite(POWER_PIN_2, HIGH);
            for(int j = 0; j < MAX_READS; j++){
                for(int i = 0; i < TSOP_NUM; i++){
                    values[i] += (digitalRead(sensors[i]) == HIGH ? 0 : 1);
                }
            }
            digitalWrite(POWER_PIN_1, LOW);
            digitalWrite(POWER_PIN_2, LOW);
            for(int i = 0; i < TSOP_NUM; i++){
                if(values[i] > index){
                    index = i;
                }
            values[i] = 0;
            }
            bestSensor = index;
            break;

        case 2: //Read w/ filtering
            digitalWrite(POWER_PIN_1, HIGH);
            digitalWrite(POWER_PIN_2, HIGH);
            for(int j = 0; j < MAX_READS; j++){
                for(int i = 0; i < TSOP_NUM; i++){
                    values[i] += (digitalRead(sensors[i]) == HIGH ? 0 : 1);
                }
            }
            digitalWrite(POWER_PIN_1, LOW);
            digitalWrite(POWER_PIN_2, LOW);
            for(int i = 0; i < TSOP_NUM; i++){
                if(values[i] < READ_THRESHOLD){
                    values[i] = 0;
                }
                if(values[i] > index){
                    index = i;
                }
            values[i] = 0;
            }
            bestSensor = index;
            break;

        case 3: //Read w/ weighting
            break;
        case 4: //Read w/ filtering & weighting
            break;
    }
}

void ReadTSOPS::reset(){
    digitalWrite(POWER_PIN_1, LOW);
    digitalWrite(POWER_PIN_2, LOW);
    delay(2);
    digitalWrite(POWER_PIN_1, HIGH);
    digitalWrite(POWER_PIN_2, HIGH);
}

void ReadTSOPS::stop(){
    digitalWrite(POWER_PIN_1, LOW);
    digitalWrite(POWER_PIN_2, LOW);
}

void ReadTSOPS::moveTangent(){ //Hmmmmm
    digitalWrite(POWER_PIN_1, HIGH);
    digitalWrite(POWER_PIN_2, HIGH);
    for(int j = 0; j < MAX_READS; j++){
        for(int i = 0; i < TSOP_NUM; i++){
            values[i] += (digitalRead(sensors[i]) == HIGH ? 0 : 1);
        }
    }
    digitalWrite(POWER_PIN_1, LOW);
    digitalWrite(POWER_PIN_2, LOW);
    for(int i = 0; i < TSOP_NUM; i++){
        if(values[i] > index){
            index = i;
        }
    values[i] = 0;
    }

    //Begin weighting
}
