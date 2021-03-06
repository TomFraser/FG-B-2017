#ifndef MotorController_h
#define MotorController_h

#include <Config.h>
#include <Pins.h>
#include <Defines.h>
#include <Arduino.h>
#include <Motor.h>
#include <Common.h>

//This library needs to be able to both play 'follow the ball' and face the ball modes because the defender robot will track the ball when defending and once it recieves the ball, it will
//go into an offensive mode.

class MotorController{
public:
    bool playDefense(double goalAngle, double lightAngle, double ballRotation, double speed);// If this method returns true, the ball is being seen
    bool playOffense(double angle, double lightAngle, double rotation, int speed); //If this method returns true, then for the next 0.5 seconds, the speed needs to be set to 30

    double doubleAbs(double value);
    int sign(double value);

    double getCompass();

    #if ROBOT
    //OBot
    Motor motorD = Motor(MOTOR_A_PWM, MOTOR_A_DIR, MOTOR_A_BRK, MOTOR_A_REV); //Really Motor D
    Motor motorC = Motor(MOTOR_B_PWM, MOTOR_B_DIR, MOTOR_B_BRK, MOTOR_B_REV); //Really Motor A
    Motor motorB = Motor(MOTOR_C_PWM, MOTOR_C_DIR, MOTOR_C_BRK, MOTOR_C_REV);
    Motor motorA = Motor(MOTOR_D_PWM, MOTOR_D_DIR, MOTOR_D_BRK, MOTOR_D_REV);
    #else
    //P2 Bot
    Motor motorD = Motor(MOTOR_A_PWM, MOTOR_A_DIR, MOTOR_A_BRK, MOTOR_A_REV);
    Motor motorC = Motor(MOTOR_B_PWM, MOTOR_B_DIR, MOTOR_B_BRK, MOTOR_B_REV);
    Motor motorB = Motor(MOTOR_C_PWM, MOTOR_C_DIR, MOTOR_C_BRK, MOTOR_C_REV);
    Motor motorA = Motor(MOTOR_D_PWM, MOTOR_D_DIR, MOTOR_D_BRK, MOTOR_D_REV); //B + rev
    #endif


private:
    int angleArray[4] = {60, 135, 225, 300};
};

#endif
