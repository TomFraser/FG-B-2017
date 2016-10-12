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

void ReadTSOPS::readMode(int mode){
    bestSensor = 0;
    index = 0;

    switch(mode){
        case 0: //Nothing
            break;
        case 1: //Reading
            read();
            break;

        case 2: //Read w/ filtering
            read();
            break;

        case 3: //Read w/ weighting
            read();
            break;
        case 4: //Read w/ filtering & weighting
            read();
            break;
    }
}

void ReadTSOPS::read(){

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
            index = i + 1;
        }
        values[i] = 0;
    }
    bestSensor = index;
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

double ReadTSOPS::moveTangent(){ //Hmmmmm This shouldnt be done here, it should be done later down the course.
    read();
    //Begin weighting
    angleToBall = index * 20.00;

    if(angleToBall != 0){
        return angleToBall < 180 ? (angleToBall + 90) : (angleToBall - 90);
    }
    return 0;

    // if(angleToBall < 180.00 && angleToBall != 0){
    //     return angleToBall + 90.00;
    // }
    // if(angleToBall > 180.00 && angleToBall != 0){
    //     return angleToBall - 90.00;ID
    // }
    // return 0;
}
