#include <MotorController.h>

bool MotorController::playDefense(double goalAngle, double lightAngle, double ballRotation, double speed){
    // In this mode we need to take angle as rotation and ignore the actual rotation.
    if(goalAngle != NO_BALL){
        motorA.set((cos(((angleArray[0] + 90) * angToRad) - (goalAngle * angToRad))) * (speed*2.55) + ballRotation);
        motorB.set((cos(((angleArray[1] + 90) * angToRad) - (goalAngle * angToRad))) * (speed*2.55) + ballRotation);
        motorC.set((cos(((angleArray[2] + 90) * angToRad) - (goalAngle * angToRad))) * (speed*2.55) + ballRotation);
        motorD.set((cos(((angleArray[3] + 90) * angToRad) - (goalAngle * angToRad))) * (speed*2.55) + ballRotation);
        return true;
    }else{
        motorA.set(0 + ballRotation);
        motorB.set(0 + ballRotation);
        motorC.set(0 + ballRotation);
        motorD.set(0 + ballRotation);
        return false;
    }
}

bool MotorController::playOffense(double angle, double lightAngle, double rotation, double speed){ //<-- The rotation passed here is external rotastion and compass will
    //still be done unless this value is greater than 0.
    if(rotation == NO_ROTATION){
        rotation = rotationController.rotate(); //Getting Compass
    }
    if(speed == NO_SPEED){
        speed = SPEED_VAL; //Defaulting to normal speed
    }

    if(lightAngle != NO_LIGHT){
        motorA.set((cos(((angleArray[0] + 90) * angToRad) - (lightAngle * angToRad))) * (COME_BACK_IN_SPD*2.55) + rotation);
        motorB.set((cos(((angleArray[1] + 90) * angToRad) - (lightAngle * angToRad))) * (COME_BACK_IN_SPD*2.55) + rotation);
        motorC.set((cos(((angleArray[2] + 90) * angToRad) - (lightAngle * angToRad))) * (COME_BACK_IN_SPD*2.55) + rotation);
        motorD.set((cos(((angleArray[3] + 90) * angToRad) - (lightAngle * angToRad))) * (COME_BACK_IN_SPD*2.55) + rotation);
        return true;
    }else{
        if(angle != NO_BALL){
            motorA.set((cos(((angleArray[0] + 90) * angToRad) - (angle * angToRad))) * (speed*2.55) + rotation);
            motorC.set((cos(((angleArray[2] + 90) * angToRad) - (angle * angToRad))) * (speed*2.55) + rotation);
            motorD.set((cos(((angleArray[3] + 90) * angToRad) - (angle * angToRad))) * (speed*2.55) + rotation);
            return false;
        }else{
            motorA.set(0 + rotation);
            motorB.set(0 + rotation);
            motorC.set(0 + rotation);
            motorD.set(0 + rotation);
            return false;
        }
    }
}
