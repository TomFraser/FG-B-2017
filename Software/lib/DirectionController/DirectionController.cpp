#include <DirectionController.h>

DirectionController::DirectionController(){
    light.init();
}

void DirectionController::calcMotors(double angle, double rotation){
    motorA.set((cos(((angleArray[0] + 90) * angToRad) - (angle * angToRad))) * 255); //Probs should do this motor stuff in the main application? I guess we can do it here tho. Might be less clear to observers
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

void DirectionController::combine(double tsopAngle){
    if(calcLight().seeing == false){
        calcMotors(tsopAngle, rotationController.rotate());
    }
    else{
        calcMotors(calcLight().angle/*Takes in angle to move away from line as oppose to following ball*/, rotationController.rotate());
    }
}
