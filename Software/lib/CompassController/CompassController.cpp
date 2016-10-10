#include <CompassController.h>

double CompassController::doubleMod(double value, double maxVal){
    return fmod((value + maxValue), maxValue);
}

double CompassController::calcHeading(double heading){
    if(heading > 180){
        heading = 360 - heading;
        return -heading;
    }
    else{
        return heading;
    }
}
