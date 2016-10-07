#include <MotorController.h>

MotorController::MotorController(){
}

void MotorController::setAngle(int angle){
    cos(((angleArray[0] + 90) * angToRad) - (angle * angToRad)); //Needs motor.set stuffs
    cos(((angleArray[1] + 90) * angToRad) - (angle * angToRad));
    cos(((angleArray[2] + 90) * angToRad) - (angle * angToRad));
}

void MotorController::setAnlge(int angle, int dirNum){
    int newAngle = (abs(round(angle/(360*1/dirNum))))*(360*1/dirNum);

    if(newAngle != -1){
        double direction = newAngle < 180 ? (newAngle + 90) : (newAngle - 90);
    }
}
