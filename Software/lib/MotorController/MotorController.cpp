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
    // if(speed == NO_SPEED){
    //     speed = SPEED_VAL; //Defaulting to normal speed
    // }

    int lowerBoundLight = mod((lightAngle - 45), 360);
    int upperBoundLight = mod((lightAngle + 45), 360);
    if(lightAngle == 0.00){
        // Serial.println("LIGHT ANGLE");
        angle = angle;
        lightAngle = 0.00;
    }else{
        if(smallestAngleBetween(angle, lightAngle) > 60){ //We need to move on a bound

            if((mod(lightAngle + 180, 360) - angle) > 0 && (mod(lightAngle + 180, 360) - angle) < 180){
                angle = upperBoundLight;
                lightAngle = 0.00;

                // Serial.println("SMALLEST U");
            }else{
                angle = lowerBoundLight;
                lightAngle = 0.00;

                // Serial.println("SMALLEST L");
            }
        }else{
            // Serial.println("OTHER");
            angle=angle;
            lightAngle = 0.00;
        }
    }

    // Serial.println(angle);

    if(lightAngle != NO_LIGHT){
        motorA.set((cos(((angleArray[0] + 90) * angToRad) - (lightAngle * angToRad))) * (COME_BACK_IN_SPD*2.55) + rotation);
        motorB.set((cos(((angleArray[1] + 90) * angToRad) - (lightAngle * angToRad))) * (COME_BACK_IN_SPD*2.55) + rotation);
        motorC.set((cos(((angleArray[2] + 90) * angToRad) - (lightAngle * angToRad))) * (COME_BACK_IN_SPD*2.55) + rotation);
        motorD.set((cos(((angleArray[3] + 90) * angToRad) - (lightAngle * angToRad))) * (COME_BACK_IN_SPD*2.55) + rotation);
        return true;
    }else{
        if(angle != NO_BALL){
            double motorAPWM = (cos(((angleArray[0] + 90) * angToRad) - (angle * angToRad)));
            double motorBPWM = (cos(((angleArray[1] + 90) * angToRad) - (angle * angToRad)));
            double motorCPWM = (cos(((angleArray[2] + 90) * angToRad) - (angle * angToRad)));
            double motorDPWM = (cos(((angleArray[3] + 90) * angToRad) - (angle * angToRad)));

            double scaledSpeed = (double) 45/(fmax(fmax(fmax(doubleAbs(motorAPWM), doubleAbs(motorBPWM)), doubleAbs(motorCPWM)), doubleAbs(motorDPWM)));
            scaledSpeed = scaledSpeed * 2.55;

            if(angle == 0.00){
                motorA.set((cos(((angleArray[0] + 90) * angToRad) - (lightAngle * angToRad))) * (100*2.55) + rotation);
                motorB.set((cos(((angleArray[1] + 90) * angToRad) - (lightAngle * angToRad))) * (100*2.55) + rotation);
                motorC.set((cos(((angleArray[2] + 90) * angToRad) - (lightAngle * angToRad))) * (100*2.55) + rotation);
                motorD.set((cos(((angleArray[3] + 90) * angToRad) - (lightAngle * angToRad))) * (100*2.55) + rotation);
            }else{
                motorA.set(min(motorAPWM * scaledSpeed + rotation, 255));
                motorB.set(min(motorBPWM * scaledSpeed + rotation, 255));
                motorC.set(min(motorCPWM * scaledSpeed + rotation, 255));
                motorD.set(min(motorDPWM * scaledSpeed + rotation, 255));
            }

            // motorA.set((cos(((angleArray[0] + 90) * angToRad) - (lightAngle * angToRad))) * (SPEED_VAL*2.55) + rotation);
            // motorB.set((cos(((angleArray[1] + 90) * angToRad) - (lightAngle * angToRad))) * (SPEED_VAL*2.55) + rotation);
            // motorC.set((cos(((angleArray[2] + 90) * angToRad) - (lightAngle * angToRad))) * (SPEED_VAL*2.55) + rotation);
            // motorD.set((cos(((angleArray[3] + 90) * angToRad) - (lightAngle * angToRad))) * (SPEED_VAL*2.55) + rotation);
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

int MotorController::sign(double value) {
    return value >= 0 ? 1 : -1;
}

double MotorController::doubleAbs(double value) {
    return value * sign(value);
}
