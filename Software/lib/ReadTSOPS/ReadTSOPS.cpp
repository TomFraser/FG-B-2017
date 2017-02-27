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

void ReadTSOPS::read(){
    bestSensor = 0;
    index = 0;
    digitalWrite(POWER_PIN_1, HIGH);
    digitalWrite(POWER_PIN_2, HIGH);
    for(int j = 0; j < MAX_READS; j++){
        for(int i = 0; i < TSOP_NUM; i++){
            values[i] += (digitalRead(sensors[i]) == HIGH ? 0 : 1);
        }
    }
    digitalWrite(POWER_PIN_1, LOW);
    digitalWrite(POWER_PIN_2, LOW);
    delayMicroseconds(200); //We can remove this if we dont need it later.
    for(int i = 0; i < TSOP_NUM; i++){
        if(values[i] > values[index]){
            index = i; //1-12 as oppose to 0-11
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

int ReadTSOPS::moveTangent(){ //Hmmmmm This shouldnt be done here, it should be done later down the course.
    read();
    //Begin weighting
    angleToBall = index * 20.00;

    if(angleToBall != 0){
        return (int)angleToBall < 180 ? (angleToBall + 90.00) : (angleToBall - 90.00);
    }
    return 0.00;

    // if(angleToBall < 180.00 && angleToBall != 0){
    //     return angleToBall + 90.00;
    // }
    // if(angleToBall > 180.00 && angleToBall != 0){
    //     return angleToBall - 90.00;
    // }
    // return 0;
}

double ReadTSOPS::findStrength(){
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
    }
    bestSensor = index;
    double tempStr = TSOP_K1 * values[bestSensor] + TSOP_K2 * (values[mod(bestSensor-1, TSOP_NUM)] + values[mod(bestSensor+1, TSOP_NUM)]) + TSOP_K3 * (values[mod(bestSensor-2, TSOP_NUM)] + values[mod(bestSensor+2, TSOP_NUM)]);
    return tempStr/16;
}

int ReadTSOPS::mod(int x,int m){
    int r = x % m;
    return r < 0 ? r + m : r;
}
