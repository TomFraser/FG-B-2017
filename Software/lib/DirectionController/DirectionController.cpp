#include <DirectionController.h>

DirectionController::DirectionController(){

}

void DirectionController::init(){
    rotationController.init();
    //light.init();
}

void DirectionController::calcMotors(double angle, double lightAngle, double rotation, double setSpeed, double altAngle){

    // if(angle == CANT_SEE_GOAL){
    //     motorController.playOffense(altAngle, lightAngle, rotation, 55);
    // }else{
    //     motorController.playDefense(angle, lightAngle, rotation, setSpeed);
    // }

    //====OFFENSE
    rotation = rotationController.rotate();
    // Serial.println(rotation);
    motorController.playOffense(angle, lightAngle, rotation, setSpeed);


    //====DEFENSE
    // motorController.playDefense(angle, lightAngle, rotation, setSpeed);


    // double universalRotation = rotation;
    // // setSpeed = min((setSpeed * 1.25), 100);
    // // double universalRotation = rotationController.rotate();
    // // double universalRotation = 0;
    // if(lightAngle != 0){
    //     // motorA.set(min(((cos(((angleArray[0] + 90) * angToRad) - (lightAngle * angToRad))) * (SPEED_VAL*2.55) + (int)universalRotation), 255));
    //     // motorB.set(min(((cos(((angleArray[1] + 90) * angToRad) - (lightAngle * angToRad))) * (SPEED_VAL*2.55) + (int)universalRotation), 255));
    //     // motorC.set(min(((cos(((angleArray[2] + 90) * angToRad) - (lightAngle * angToRad))) * (SPEED_VAL*2.55) + (int)universalRotation), 255));
    //     // motorD.set(min(((cos(((angleArray[3] + 90) * angToRad) - (lightAngle * angToRad))) * (SPEED_VAL*2.55) + (int)universalRotation), 255));
    //
    //     motorA.set((cos(((angleArray[0] + 90) * angToRad) - (lightAngle * angToRad))) * (setSpeed*2.55) + (int)universalRotation); //Light Movement
    //     motorB.set((cos(((angleArray[1] + 90) * angToRad) - (lightAngle * angToRad))) * (setSpeed*2.55) + (int)universalRotation);
    //     motorC.set((cos(((angleArray[2] + 90) * angToRad) - (lightAngle * angToRad))) * (setSpeed*2.55) + (int)universalRotation);
    //     motorD.set((cos(((angleArray[3] + 90) * angToRad) - (lightAngle * angToRad))) * (setSpeed*2.55) + (int)universalRotation);
    // }else{
    //     if(angle != 65506.00){
    //         motorA.set((cos(((angleArray[0] + 90) * angToRad) - (angle * angToRad))) * (setSpeed*2.55) + (int)universalRotation);
    //         motorB.set((cos(((angleArray[1] + 90) * angToRad) - (angle * angToRad))) * (setSpeed*2.55) + (int)universalRotation);
    //         motorC.set((cos(((angleArray[2] + 90) * angToRad) - (angle * angToRad))) * (setSpeed*2.55) + (int)universalRotation);
    //         motorD.set((cos(((angleArray[3] + 90) * angToRad) - (angle * angToRad))) * (setSpeed*2.55) + (int)universalRotation);
    //     }else{
    //         motorA.set(0 + (int)universalRotation);
    //         motorB.set(0 + (int)universalRotation);
    //         motorC.set(0 + (int)universalRotation);
    //         motorD.set(0 + (int)universalRotation);
    //     }
    // }
}

void DirectionController::calcMotors(double angle, double rotation, int dirNum){
    int newAngle = (abs(round(angle/(360*1/dirNum))))*(360*1/dirNum);

    if(newAngle != -1){
        direction = newAngle < 180 ? (newAngle + 90) : (newAngle - 90);
    }

    motorA.set(((cos(((angleArray[0] + 90) * angToRad) - (direction * angToRad))) * 255) + rotation); //B
    motorB.set(((cos(((angleArray[1] + 90) * angToRad) - (direction * angToRad))) * 255) + rotation); //A
    motorC.set(((cos(((angleArray[2] + 90) * angToRad) - (direction * angToRad))) * 255) + rotation); //C
    motorD.set(((cos(((angleArray[3] + 90) * angToRad) - (direction * angToRad))) * 255) + rotation); //D

    // Serial.println(((cos(((angleArray[0] + 90) * angToRad) - (direction * angToRad))) * 255) + rotation);
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
        calcMotors(tsopAngle, 0.00, 0.00);
    }
    else{
        calcMotors(calcLight().angle/*Takes in angle to move away from line as oppose to following ball*/, 0.00, 0.00);
    }
}

void DirectionController::setPWM(int pwm){
    motorA.set(pwm);
    motorB.set(pwm);
    motorC.set(pwm);
    // motorD.set(pwm);
}
