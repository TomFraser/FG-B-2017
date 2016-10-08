#include <MotorController.h>

MotorController::MotorController(){
}

void MotorController::setAngle(int angle){
    (cos(((angleArray[0] + 90) * angToRad) - (angle * angToRad))) * 255; //Needs motor.set stuffs
    (cos(((angleArray[1] + 90) * angToRad) - (angle * angToRad))) * 255;
    (cos(((angleArray[2] + 90) * angToRad) - (angle * angToRad))) * 255;
}

void MotorController::setAnlge(int angle, int dirNum){
    int newAngle = (abs(round(angle/(360*1/dirNum))))*(360*1/dirNum);

    if(newAngle != -1){
        double direction = newAngle < 180 ? (newAngle + 90) : (newAngle - 90);
    }

    (cos(((angleArray[0] + 90) * angToRad) - (direction * angToRad))) * 255;
    (cos(((angleArray[1] + 90) * angToRad) - (direction * angToRad))) * 255;
    (cos(((angleArray[2] + 90) * angToRad) - (direction * angToRad))) * 255;
}
