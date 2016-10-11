#include <DirectionController.h>

DirectionController::DirectionController(){
}

void DirectionController::setAngle(int angle){
    motorA.set((cos(((angleArray[0] + 90) * angToRad) - (angle * angToRad))) * 255); //Needs motor.set stuffs
    motorB.set((cos(((angleArray[1] + 90) * angToRad) - (angle * angToRad))) * 255);
    motorC.set((cos(((angleArray[2] + 90) * angToRad) - (angle * angToRad))) * 255);
}

void DirectionController::setAnlge(int angle, int dirNum){
    int newAngle = (abs(round(angle/(360*1/dirNum))))*(360*1/dirNum);

    if(newAngle != -1){
        direction = newAngle < 180 ? (newAngle + 90) : (newAngle - 90);
    }

    motorA.set((cos(((angleArray[0] + 90) * angToRad) - (direction * angToRad))) * 255);
    motorB.set((cos(((angleArray[1] + 90) * angToRad) - (direction * angToRad))) * 255);
    motorC.set((cos(((angleArray[2] + 90) * angToRad) - (direction * angToRad))) * 255);
}
