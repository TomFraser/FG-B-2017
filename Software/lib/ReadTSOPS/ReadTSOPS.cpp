#include <ReadTSOPS.h>

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
    // values[5] = 0;
    // values[6] = 0;
    digitalWrite(POWER_PIN_1, LOW);
    digitalWrite(POWER_PIN_2, LOW);
    delayMicroseconds(1000);
    for(int i = 0; i < TSOP_NUM; i++){
        // Filtering
        if(values[i] < TSOP_MIN_THRESHOLD){
            values[i] = 0;
        }
        if(values[i] > 300){
            values[i] = 0;
        }
        if(values[i] > value_index){
            index = i;
            value_index = values[i];
        }
        values[i] = 0;
    }
    bestSensor = index;
    // Serial.println(bestSensor);
    // Serial.println(value_index);
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

int ReadTSOPS::moveAngle(){
    read();
    angleToBall = index * 30.00;

    return (int)calculateOrbitSimple(angleToBall, false);
    // return (int)calculateOrbitComplex(angleToBall);
    // return (int)calculateTSOPAverage();
}

double ReadTSOPS::calculateStrength(){
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
    delayMicroseconds(3000);
    for(int i = 0; i < TSOP_NUM; i++){
        if(values[i] < 30){
            values[i] = 0;
        }
        if(values[i] > 500){
            values[i] = 0;
        }
        if(values[i] > value_index){
            index = i + 1;
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

double ReadTSOPS::calculateOrbitSimple(double angleIn, bool useFirst){
        if(useFirst){
    //     if(angleIn <= TSOP_FORWARD_LOWER || angleIn >= TSOP_FORWARD_UPPER){
    //         return angleIn;
    //     }else{
    //         return angleIn < 180 ? (angleIn + TSOP_ORBIT_ANGLE) : (angleIn - TSOP_ORBIT_ANGLE);
    //     }
        return angleIn;
    }else{
        if(angleIn == -30){
            return angleIn;
        }else if(angleIn <= TSOP_FORWARD_LOWER || angleIn >= TSOP_FORWARD_UPPER){
            scaledStrength = (value_index + previousValue_index)/2;
            previousValue_index = value_index;
            // scaledAngle = (angleIn + previousIndex)/2;
            previousIndex = angleIn;
            // Serial.println(angleIn < 180 ? (angleIn + (angleIn/100 * 90)) : (angleIn - ((360-angleIn)/100 * 90)));
            // return angleIn < 180 ? (angleIn + ((-0.5 * cos(2*(angleIn * angToRad)) + 0.5) * (65))) : angleIn - ((-0.5 * cos(2*(angleIn * angToRad)) + 0.5) * (65));
            // Serial.println(angleIn < 180 ? (angleIn + (angleIn/120 * 150)) : (angleIn - ((360-angleIn)/120 * 150)));
            return angleIn < 180 ? (angleIn + (angleIn/120 * 90)) : (angleIn - ((360-angleIn)/120 * 90));
        }else{
            int tsop = angleIn/30;
            int frontalChange = tsop < 6 ? (tsop) : (TSOP_NUM - tsop);
            scaledAngle = (angleIn + previousIndex)/2;
            previousIndex = angleIn;
            // if(scaledStrength >= TSOP_MIN_VAL_INDEX){
            // Serial.println(angleIn < 180 ? (angleIn + 90) : (angleIn - 90));
                return angleIn < 180 ? (angleIn + 65) : (angleIn - 65);
            // }else{
                // return scaledAngle;
            // }
        }
    }
}

double ReadTSOPS::calculateOrbitComplex(double angleIn){
    if(angleIn == -30){
        return angleIn;
    }else if(angleIn <= TSOP_FORWARD_LOWER_ED || angleIn >= TSOP_FORWARD_UPPER_ED){

        int frontalChange = angleIn < 180 ? (angleIn) : (abs(angleIn-360));

        return angleIn < 180 ? (angleIn + ((1/8100)*pow(frontalChange, 2) * 90)) : (angleIn - ((1/8100)*pow(frontalChange, 2) * 90));
    }else{
        return angleIn < 180 ? (angleIn + 75) : (angleIn - 75);
    }
}

// double ReadTSOPS::calculateTSOPAverage(){
//     bestSensor = secondSensor = thirdSensor = 0;
//     value_index = 0;
//     index = tsop2 = tsop3 = -1;
//     digitalWrite(POWER_PIN_1, HIGH);
//     digitalWrite(POWER_PIN_2, HIGH);
//     for(int j = 0; j < MAX_READS; j++){
//         for(int i = 0; i < TSOP_NUM; i++){
//             values[i] += (digitalRead(sensors[i]) == HIGH ? 0 : 1);
//         }
//     }
//     digitalWrite(POWER_PIN_1, LOW);
//     digitalWrite(POWER_PIN_2, LOW);
//     delayMicroseconds(1000);
//     for(int i = 0; i < TSOP_NUM; i++){
//         if(values[i] > value_index){
//             tsop3 = tsop2;
//             tsop2 = index;
//             index = i;
//             value_index = values[i];
//         }
//         values[i] = 0;
//     }
//     bestSensor = index;
//     secondSensor = tsop2;
//     thirdSensor = tsop3;
//     // If this doesnt work, mess with the dividers
//     double averagedAngle = bestSensor + (secondSensor - bestSensor)/2 + (thirdSensor - bestSensor)/5;
//     return averagedAngle;
// }

double ReadTSOPS::calculateTSOPAverage() {

}
