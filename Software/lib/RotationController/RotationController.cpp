#include <RotationController.h>

RotationController::RotationController(){

}

void RotationController::init(){
    compass.init();
    delay(10);
    compass.calibrate();
}

bool RotationController::getPixy(){
    if(pixy.getBlocks()){ //seing the block
        blockHeight = pixy.blocks[0].height;
        blockWidth = pixy.blocks[0].width;
        blockX = pixy.blocks[0].x;
        blockY = pixy.blocks[0].y;
        return true;
    }
    return false;
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
    if(pixy.getBlocks()){
        return (calcPixy() * PIXY_MULTIPLIER); //Returns Pixy rotation when seeing goal
    }else{
        compass.update();
        compassHeading = compass.getHeading();
        compassHeading = (compassHeading * COMPASS_MULTIPLIER);
        return compassHeading; //Returns compass when no goal is seen
    }
}
