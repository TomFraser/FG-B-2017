#include <RotationController.h>

RotationController::RotationController(){

}

void RotationController::init(){
    compass.init();
    Serial.println("Compass Init Done");
    compass.calibrate();
    Serial.println("Calibration Done");
}

bool RotationController::getPixy(){
    // if(pixy.getBlocks()){ //seing the block
        // blockHeight = pixy.blocks[0].height;
        // blockWidth = pixy.blocks[0].width;
        // blockX = pixy.blocks[0].x;
        // blockY = pixy.blocks[0].y;
        // return true;
    // }
    return false;
}

void RotationController::getCompass(){
    compass.update();
    compassHeading = compass.getHeading();
    Serial.println(compassHeading);
}


void RotationController::calcPixy(){
    if(getPixy()){
        if(blockX >= PIXY_CENTRE_X){
            rotationToAdd = blockX - PIXY_CENTRE_X;
        }
        else if(blockX <= PIXY_CENTRE_X){
            rotationToAdd = PIXY_CENTRE_X - blockX;
        }
    }
    else{
        rotationToAdd = 0;
    }
}

void RotationController::calcRotation(){
    newTarget = compassHeading > 180 ? compassHeading - rotationToAdd : compassHeading + rotationToAdd;
    compass.setTarget(newTarget);
}

double RotationController::rotate(){
    compass.update();
    finalRotation = compass.getHeading();
}
