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
}


void RotationController::calcPixy(){
    if(getPixy()){
        if(blockX >= PIXY_CENTRE_X){
            rotation.toAdd = blockX - PIXY_CENTRE_X;
        }
        else if(blockX <= PIXY_CENTRE_X){
            rotation.toAdd = PIXY_CENTRE_X - blockX;
        }
    }
}

void RotationController::setRotation(){
    compass.update();
    int finalRotation = compass.read();
}

int RotationController::rotate(){
    return finalRotation;
}
