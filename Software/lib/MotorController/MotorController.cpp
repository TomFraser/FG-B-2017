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

bool MotorController::move(double angle, double rotation, int speed, bool followingBall){ //<-- The rotation passed here is external rotastion and compass will
    if(angle != NO_BALL && speed != 0){
        double motorAPWM = (cos(((angleArray[0] + 90 - angle) * angToRad)));
        double motorBPWM = (cos(((angleArray[1] + 90 - angle) * angToRad)));
        double motorCPWM = (cos(((angleArray[2] + 90 - angle) * angToRad)));
        double motorDPWM = (cos(((angleArray[3] + 90 - angle) * angToRad)));

        double scaledSpeed = (double)255/doubleAbs(fmax(fmax(fmax(doubleAbs(motorAPWM), doubleAbs(motorBPWM)), doubleAbs(motorCPWM)), doubleAbs(motorDPWM)));

        int motorASpeed = (motorAPWM * scaledSpeed) + rotation;
        int motorBSpeed = (motorBPWM * scaledSpeed) + rotation;
        int motorCSpeed = (motorCPWM * scaledSpeed) + rotation;
        int motorDSpeed = (motorDPWM * scaledSpeed) + rotation;

        double scaledSpeed2 = (double) 255/doubleAbs(fmax(fmax(fmax(doubleAbs(motorASpeed), doubleAbs(motorBSpeed)), doubleAbs(motorCSpeed)), doubleAbs(motorDSpeed)));

        int finalSpeedA = (motorASpeed * scaledSpeed2)/100 * speed;
        int finalSpeedB = (motorBSpeed * scaledSpeed2)/100 * speed;
        int finalSpeedC = (motorCSpeed * scaledSpeed2)/100 * speed;
        int finalSpeedD = (motorDSpeed * scaledSpeed2)/100 * speed;

        if((angle <= 15 || angle >= 345) && followingBall){
            motorA.set(min((cos(((angleArray[0] + 90) * angToRad) - (angle * angToRad))) * (FORWARD_SPEED*2.55) + rotation, 255));
            motorB.set(min((cos(((angleArray[1] + 90) * angToRad) - (angle * angToRad))) * (FORWARD_SPEED*2.55) + rotation, 255));
            motorC.set(min((cos(((angleArray[2] + 90) * angToRad) - (angle * angToRad))) * (FORWARD_SPEED*2.55) + rotation, 255));
            motorD.set(min((cos(((angleArray[3] + 90) * angToRad) - (angle * angToRad))) * (FORWARD_SPEED*2.55) + rotation, 255));
        }else{
            motorA.set(finalSpeedA);
            motorB.set(finalSpeedB);
            motorC.set(finalSpeedC);
            motorD.set(finalSpeedD);
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

int MotorController::sign(double value) {
    return value >= 0 ? 1 : -1;
}

double MotorController::doubleAbs(double value) {
    return value * sign(value);
}
