#include <DirectionController.h>

DirectionController::DirectionController(){
    
}

void DirectionController::init(){
    rotationController.init();
    //light.init();
}

void DirectionController::calcMotors(double angle, double rotation){
    //Solve the whole going forward while no seeing ball thing
    rotationController.getCompass();

    if(angle != 65506.00){
        motorA.set((cos(((angleArray[0] + 90) * angToRad) - (angle * angToRad))) * (SPEED_VAL*2.55)); //Probs should do this motor stuff in the main application? I guess we can do it here tho. Might be less clear to observers
        motorB.set((cos(((angleArray[1] + 90) * angToRad) - (angle * angToRad))) * (SPEED_VAL*2.55));
        motorC.set((cos(((angleArray[2] + 90) * angToRad) - (angle * angToRad))) * (SPEED_VAL*2.55));
        motorD.set((cos(((angleArray[3] + 90) * angToRad) - (angle * angToRad))) * (SPEED_VAL*2.55));
    }else{
        motorA.set(0);
        motorB.set(0);
        motorC.set(0);
        motorD.set(0);
    }
}

void DirectionController::calcMotors(double angle, double rotation, int dirNum){
    int newAngle = (abs(round(angle/(360*1/dirNum))))*(360*1/dirNum);

    if(newAngle != -1){
        direction = newAngle < 180 ? (newAngle + 90) : (newAngle - 90);
    }

    motorA.set(((cos(((angleArray[0] + 90) * angToRad) - (direction * angToRad))) * 255) + rotation);
    motorB.set(((cos(((angleArray[1] + 90) * angToRad) - (direction * angToRad))) * 255) + rotation);
    motorC.set(((cos(((angleArray[2] + 90) * angToRad) - (direction * angToRad))) * 255) + rotation);
    motorD.set(((cos(((angleArray[3] + 90) * angToRad) - (direction * angToRad))) * 255) + rotation);
}

lightStruct DirectionController::calcLight(){
    values = {false, 0};
    //light.readLight();
    //light.averageAngles();
    //lightAngle = light.getAngle();
    if(lightAngle >= 0){
        values = {true, lightAngle};
        return values;
    }
    else{
        return values;
    }
}

void DirectionController::move(double tsopAngle){
    if(calcLight().seeing == false){
        calcMotors(tsopAngle, /*rotationController.rotate()*/0.00);
    }
    else{
        calcMotors(calcLight().angle/*Takes in angle to move away from line as oppose to following ball*/, /*rotationController.rotate()*/0.00);
    }
}

void DirectionController::setPWM(int pwm){
    motorA.set(pwm);
    motorB.set(pwm);
    motorC.set(pwm);
    motorD.set(pwm);
}
