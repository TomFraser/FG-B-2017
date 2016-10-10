#include <TsopController.h>

uint16_t TsopController::activateTsop(){
    bestSensor = 0;
    toSend = 0;
    bestSensor = TSOPS.moveTangent();
    toSend = bestSensor;
    return toSend;
}
