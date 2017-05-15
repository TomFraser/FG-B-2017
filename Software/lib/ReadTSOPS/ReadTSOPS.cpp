#include <ReadTSOPS.h>
#include <Arduino.h>

ReadTSOPS::ReadTSOPS(){
    for(int i = 0; i < TSOP_NUM; i++){
        pinMode(sensors[i], INPUT_PULLUP);
    }
    pinMode(POWER_PIN_1, OUTPUT);
    pinMode(POWER_PIN_2, OUTPUT);

    bestSensor = 0;
    index = 0;
}

void ReadTSOPS::read(){
    bestSensor = 0;
    value_index = 0;
    index = -1;
    digitalWrite(POWER_PIN_1, HIGH);
    digitalWrite(POWER_PIN_2, HIGH);
    for(int j = 0; j < MAX_READS; j++){
        for(int i = 0; i < TSOP_NUM; i++){
            values[i] += (digitalRead(sensors[i]) == HIGH ? 0 : 1);
        }
    }
    digitalWrite(POWER_PIN_1, LOW);
    digitalWrite(POWER_PIN_2, LOW);
    delayMicroseconds(1000); //We can remove this if we dont need it later.
    for(int i = 0; i < TSOP_NUM; i++){
        // Filtering
        if(values[i] < TSOP_MIN_THRESHOLD){
            values[i] = 0;
        }
        if(values[i] > value_index){
            index = i; //1-12 as oppose to 0-11
            value_index = values[i];
            // Serial.println(value_index);
        }
        // Serial.println(values[i]);
        values[i] = 0;
    }
    bestSensor = index;
    // Serial.println(bestSensor);
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
    angleToBall = index * 30.00;

    return (int)correctOrbit(angleToBall, false);
    return (int)angleToBall;
}

double ReadTSOPS::findStrength(){
     bestSensor = 0;
    value_index = 0;
    index = 0;
    for(int i = 0; i < TSOP_NUM; i++){
        values[i] = 0;
    }
    digitalWrite(POWER_PIN_1, HIGH);
    digitalWrite(POWER_PIN_2, HIGH);
    for(int j = 0; j < MAX_READS; j++){
        for(int i = 0; i < TSOP_NUM; i++){
            values[i] += (digitalRead(sensors[i]) == HIGH ? 0 : 1);
        }
    }
    digitalWrite(POWER_PIN_1, LOW);
    digitalWrite(POWER_PIN_2, LOW);
    delayMicroseconds(3000); //We can remove this if we dont need it later.
    for(int i = 0; i < TSOP_NUM; i++){
        // Filtering
        if(values[i] < 30){
            values[i] = 0;
        }
        if(values[i] > 500){
            values[i] = 0;
        }
        if(values[i] > value_index){
            index = i + 1; //1-12 as oppose to 0-11
            value_index = values[i];
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

double ReadTSOPS::correctOrbit(double angleIn, bool useFirst){
    // Serial.println(angleIn);
    if(useFirst){
        if(angleIn <= TSOP_FORWARD_LOWER || angleIn >= TSOP_FORWARD_UPPER){
            return angleIn;
        }else{
            return angleIn < 180 ? (angleIn + TSOP_ORBIT_ANGLE) : (angleIn - TSOP_ORBIT_ANGLE);
        }
    }else{
        if(angleIn == -30){
            return angleIn;
        }else if(angleIn <= TSOP_FORWARD_LOWER || angleIn >= TSOP_FORWARD_UPPER){
            //-50cos3x+50 (Maybe) [Confirmed]
            // Serial.println(angleIn < 180 ? (-50*cos(3*angleIn)+50) : -(-50*cos(3*angleIn)+50));
            return angleIn < 180 ? (-50*cos(2*(angleIn*angToRad))+50) : 360-(-50*cos(3*angleIn)+50);
        }else{
            int tsop = angleIn/30;
            int frontalChange = tsop < 6 ? (tsop) : (TSOP_NUM - tsop);
            return tsop < 6 ? (constrain(angleIn + TSOP_ORBIT_ANGLE_15 * frontalChange, 0.00, 270)) : (constrain(angleIn - TSOP_ORBIT_ANGLE_15 * frontalChange, 90.00, 360));
        }
    }

    //Old Orbit - I might be an idiot
    //Theoretical Values for this: [ 126, 144, 162, 180, 198, 180, 198, 216, 234 ]

    // if(angleIn == -30.0 || angleIn <= TSOP_FORWARD_LOWER || angleIn >= TSOP_FORWARD_UPPER){
    //     return angleIn;
    // }else{
    //     int selectedTsop = angleIn/30;
    //     int inVar = angleIn < 180.00 ? (selectedTsop) : (TSOP_NUM - selectedTsop);
    //     int variableRotate = angleIn < 180.00 ? (TSOP_VARIABLE_ANGLE * inVar + 90) : (360 - TSOP_VARIABLE_ANGLE * inVar - 90);
    //     // int variableRotate = constrain(TSOP_VARIABLE_ANGLE * inVar, 0.00, angleIn < 180.00 ? (angleIn - TSOP_ORBIT_ANGLE) : (angleIn + TSOP_ORBIT_ANGLE));
    //     return variableRotate;
    // }
    //
}
