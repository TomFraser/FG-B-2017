#include <RotationController.h>

RotationController::RotationController(){

}

void RotationController::init(){
    delay(10);
}

bool RotationController::getPixy(){
    // Serial.println("pixy Go");
    return false;
}

double RotationController::getCompass(){
    return 0.00;
}

double RotationController::rawCompass(){
    return 0.00;
}


// double RotationController::calcPixy(){
//         blockX = pixy.blocks[0].x;
//         // Serial.print("W: "); Serial.print(pixy.blocks[0].width); Serial.print(" H: "); Serial.println(pixy.blocks[0].height);
//         // // if(pixy.blocks[0].width > 100 && pixy.blocks[0].height < 45){
//         // if(pixy.blocks[0].height < 50){
//         //   Serial.println("doing pixy");
//         // }
//
//         prevTime = millis();
//         prevReturn = -1*(PIXY_CENTRE_X - blockX);
//         return -1*(PIXY_CENTRE_X - blockX);
// }

void RotationController::calcRotation(){
    // newTarget = compassHeading > 180 ? compassHeading - rotationToAdd : compassHeading + rotationToAdd;
    // compass.setTarget(newTarget);
}

double RotationController::rotate(int rotationData, int goalData, int goalSize){
    compassHeading = (rotationData * COMPASS_MULTIPLIER);
    compassHeading = PIDRotation(compassHeading);

    if (goalSize < GOAL_SIZE_THRESHOLD){ //If not seeing goal, do compass
        if(compassHeading <= 0){ //Negative
            if(compassHeading < COMPASS_ABS_MAX_NEG){
                return COMPASS_ABS_MAX_NEG;
            }else{
                return compassHeading;
            }
        }else{
            if(compassHeading > COMPASS_ABS_MAX){
                return COMPASS_ABS_MAX;
            }else{
                return compassHeading;
            }
        }
        return absCompassHeading; //Returns compass when no goal is seen
    }else{ //If seeing goal, do goal facing
        goalHeading = ((((int)goalData + 180)%360) - 180);
        //Serial.println(goalHeading);
        goalHeading = (goalHeading * GOAL_MULTIPLIER);
        if(goalHeading <= 0 && goalData != -30){ //Negative
            if(goalHeading < COMPASS_ABS_MAX_NEG){
                return COMPASS_ABS_MAX_NEG;
            }else{
                return compassHeading;
            }
        }else if(goalData != -30){
            if(goalHeading > COMPASS_ABS_MAX){
                return COMPASS_ABS_MAX;
            }else{
                return goalHeading;
            }
        }
        else{
            return 0;
        }
    }
}

double RotationController::PIDRotation(double rotationIn){
    double derivative = (rotationIn - lastAngle) / (millis() - lastTime);
    lastTime = millis();
    lastAngle = rotationIn;
    return rotationIn * CONST_K + derivative * CONST_J;
}
