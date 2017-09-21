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


double RotationController::calcPixy(){
        blockX = pixy.blocks[0].x;
        prevTime = millis();
        prevReturn = -1*(PIXY_CENTRE_X - blockX);
        return -1*(PIXY_CENTRE_X - blockX);
}

void RotationController::calcRotation(){
    // newTarget = compassHeading > 180 ? compassHeading - rotationToAdd : compassHeading + rotationToAdd;
    // compass.setTarget(newTarget);
}

double RotationController::rotate(int rotationData){
    compassHeading = (rotationData * COMPASS_MULTIPLIER);
    compassHeading = PIDRotation(compassHeading);
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
}

double RotationController::PIDRotation(double rotationIn){
    double derivative = (rotationIn - lastAngle) / (millis() - lastTime);
    lastTime = millis();
    lastAngle = rotationIn;
    return rotationIn * CONST_K + derivative * CONST_J;
}
