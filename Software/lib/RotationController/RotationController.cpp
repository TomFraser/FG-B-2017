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

double RotationController::rotate(int rotationData){
    compassHeading = (rotationData * COMPASS_MULTIPLIER);
    compassHeading = PIDRotation(compassHeading);

    // if(millis() > prevTime + 20){
        // if(pixy.getBlocks() && pixy.blocks[0].height < 50){
        // if(pixy.getBlocks()){
        //     int pixyHeading = calcPixy();
        //     pixyHeading = pixyHeading * PIXY_MULTIPLIER;
        //
        //     if(pixyHeading <= 0){
        //         if(pixyHeading < PIXY_ABS_MAX_NEG){
        //             prevPixy = PIXY_ABS_MAX_NEG;
        //             return PIXY_ABS_MAX_NEG;
        //         }else{
        //             prevPixy = pixyHeading;
        //             return pixyHeading;
        //         }
        //     }else{
        //         if(pixyHeading > PIXY_ABS_MAX){
        //             prevPixy = PIXY_ABS_MAX;
        //             return PIXY_ABS_MAX;
        //         }else{
        //             prevPixy = pixyHeading;
        //             return pixyHeading;
        //         }
        //     }
        // }else{
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
        // }
    // }else{
    //     // double __return = prevReturn * PIXY_MULTIPLIER;
    //     // if(__return > 60){
    //     //     return 60;
    //     // }else if(__return < -60){
    //     //     return -60;
    //     // }else{
    //     //     return __return;
    //     // }
    //     return prevPixy/2.25;
    // }
}

double RotationController::PIDRotation(double rotationIn){
    double derivative = (rotationIn - lastAngle) / (millis() - lastTime);
    lastTime = millis();
    lastAngle = rotationIn;
    return rotationIn * CONST_K + derivative * CONST_J;
}
