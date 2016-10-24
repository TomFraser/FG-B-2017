#include <DirectionController.h>

DirectionController::DirectionController(){
    light.init();
}

void DirectionController::calcMotors(double angle, double rotation){
    motorA.set((cos(((angleArray[0] + 90) * angToRad) - (angle * angToRad))) * 255); //Needs motor.set stuffs
    motorB.set((cos(((angleArray[1] + 90) * angToRad) - (angle * angToRad))) * 255);
    motorC.set((cos(((angleArray[2] + 90) * angToRad) - (angle * angToRad))) * 255);
}

void DirectionController::calcMotors(double angle, double rotation, int dirNum){
    int newAngle = (abs(round(angle/(360*1/dirNum))))*(360*1/dirNum);

    if(newAngle != -1){
        direction = newAngle < 180 ? (newAngle + 90) : (newAngle - 90);
    }

    motorA.set(((cos(((angleArray[0] + 90) * angToRad) - (direction * angToRad))) * 255) + rotation);
    motorB.set(((cos(((angleArray[1] + 90) * angToRad) - (direction * angToRad))) * 255) + rotation);
    motorC.set(((cos(((angleArray[2] + 90) * angToRad) - (direction * angToRad))) * 255) + rotation);
}

lightStruct DirectionController::calcLight(){
    values = {false, 0};
    light.readLight();
    light.averageAngles();
    lightAngle = light.getAngle();
    if(lightAngle >= 0){
        values = {true, lightAngle};
    }
    else{
        return values;
    }
}

void DirectionController::calcTsops(){
    tsopAngle = tsops.moveTangent();
}

void DirectionController::combine(){
    if(calcLight().seeing == false){
        calcMotors(tsopAngle, rotationController.rotate()); //FIX!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    }
    else{
        calcMotors(calcLight().angle, rotationController.rotate());
    }
}
