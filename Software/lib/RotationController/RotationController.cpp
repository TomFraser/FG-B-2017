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
    return false;
}

double RotationController::getCompass(){
    compass.update();
    compassHeading = compass.getHeading();
    compassHeading = (compassHeading * COMPASS_MULTIPLIER);
    return compassHeading;
}

double RotationController::rawCompass(){
    compass.update();
    return compass.getHeading();
}


double RotationController::calcPixy(){
        blockX = pixy.blocks[0].x;
        prevTime = millis();
        prevReturn = -1*(PIXY_CENTRE_X - blockX);
        return -1*(PIXY_CENTRE_X - blockX);
}

void RotationController::calcRotation(){
    newTarget = compassHeading > 180 ? compassHeading - rotationToAdd : compassHeading + rotationToAdd;
    compass.setTarget(newTarget);
}

double RotationController::rotate(){
    compass.update();
    compassHeading = compass.getHeading();
    compassHeading = (compassHeading * COMPASS_MULTIPLIER);

    if(millis() > prevTime + 30){
        if(pixy.getBlocks(1)){
            int pixyHeading = calcPixy();
            pixyHeading = pixyHeading * PIXY_MULTIPLIER;

            if(pixyHeading <= 0){
                if(pixyHeading < PIXY_ABS_MAX_NEG){
                    return PIXY_ABS_MAX_NEG;
                }else{
                    return pixyHeading;
                }
            }else{
                if(pixyHeading > PIXY_ABS_MAX){
                    return PIXY_ABS_MAX;
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
    }else{
        // double __return = prevReturn * PIXY_MULTIPLIER;
        // if(__return > 60){
        //     return 60;
        // }else if(__return < -60){
        //     return -60;
        // }else{
        //     return __return;
        // }
        return 0.00;
    }
}
