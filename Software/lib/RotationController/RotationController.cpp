#include <RotationController.h>

RotationController::RotationController(){

}

void RotationController::init(){
    compass.init();
    delay(10);
    compass.calibrate();
}

bool RotationController::getPixy(){
    // Serial.println("pixy Go");
    blockHeight = pixy.blocks[0].height;
    blockWidth = pixy.blocks[0].width;
    blockX = pixy.blocks[0].x;
    blockY = pixy.blocks[0].y;
    return true;
}

double RotationController::getCompass(){
    compass.update();
    compassHeading = compass.getHeading();
    compassHeading = (compassHeading * COMPASS_MULTIPLIER);
    return compassHeading;
}


double RotationController::calcPixy(){
    if(getPixy()){
        if(blockX >= PIXY_CENTRE_X){
            return rotationToAdd = -1*(PIXY_CENTRE_X - blockX);
        }
        else if(blockX <= PIXY_CENTRE_X){
            prevReturn = -1*(PIXY_CENTRE_X - blockX);
            return -1*(PIXY_CENTRE_X - blockX);
        }
    }
    else{
        return 0.00;
    }
}

void RotationController::calcRotation(){
    newTarget = compassHeading > 180 ? compassHeading - rotationToAdd : compassHeading + rotationToAdd;
    compass.setTarget(newTarget);
}

double RotationController::rotate(){
    compass.update();
    compassHeading = compass.getHeading();
    compassHeading = (compassHeading * COMPASS_MULTIPLIER);

    if(pixy.getBlocks()){
        // return (calcPixy() * PIXY_MULTIPLIER); //Returns Pixy rotation when seeing goal
        int pixyHeading = calcPixy() * PIXY_MULTIPLIER;

        if(pixyHeading <= 0){
            if(pixyHeading < COMPASS_ABS_MAX_NEG){
                return COMPASS_ABS_MAX_NEG;
            }else{
                return pixyHeading;
            }
        }else{
            if(pixyHeading > COMPASS_ABS_MAX){
                return COMPASS_ABS_MAX;
            }else{
                return pixyHeading;
            }
        }
    }else{
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
}
