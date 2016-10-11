#include <RotationController.h>

bool RotationController::getPixy(){
    if(pixy.getBlocks()){ //seing the block
        int cam = pixy.blocks[0];
        int blockHeight = cam.height();
        int blockWidth = cam.width();
        int blockX = cam.x;
        int blockY = cam.y;
        return true;
    }
    return false;
}

void RotationController::getCompass(){
    compass.update();
    compassHeading = compass.read();
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
    compass.updateTarget(newTarget);
}

int RotationController::rotate(){
    finalRotation = compass.read();
    return finalRotation;
}
