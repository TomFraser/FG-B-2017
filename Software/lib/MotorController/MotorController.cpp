#include <MotorCotroller.h>

MotorController::MotorController(){
    Motor motorA(0,0,0,0);
    Motor motorB(0,0,0,0);
    Motor motorC(0,0,0,0);
}

void MotorController::setAngle(int angle){
    motorA.set(cos(((angleArray[0] + 90) * angleToRad) - (angle * angleToRad)));
    motorB.set(cos(((angleArray[1] + 90) * angleToRad) - (angle * angleToRad)));
    motorC.set(cos(((angleArray[2] + 90) * angleToRad) - (angle * angleToRad)));
}
