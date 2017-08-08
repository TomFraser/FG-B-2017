#ifndef DirectionController_h
#define DirectionController_h

#include <Config.h>
#include <Pins.h>
#include <Defines.h>
#include <Arduino.h>
#include <Motor.h>
#include <MotorController.h>
// #include <Light.h>
#include <ReadTSOPS.h>
#include <RotationController.h>

struct lightStruct {
    bool seeing;
    double angle;
};

class DirectionController{

public:
    DirectionController();

    void init();
    void calcMotors(double angle, double lightAngle, double rotation, double setSpeed, double altAngle);
    void calcMotors(double angle, double rotation, int dirNum);
    lightStruct calcLight();
    void move(double angle);
    void setPWM(int pwm);

    Motor motorD = Motor(MOTOR_A_PWM, MOTOR_A_DIR, MOTOR_A_BRK, MOTOR_A_REV);
    Motor motorC = Motor(MOTOR_B_PWM, MOTOR_B_DIR, MOTOR_B_BRK, MOTOR_B_REV);
    Motor motorA = Motor(MOTOR_C_PWM, MOTOR_C_DIR, MOTOR_C_BRK, MOTOR_C_REV);
    Motor motorB = Motor(MOTOR_D_PWM, MOTOR_D_DIR, MOTOR_D_BRK, MOTOR_D_REV); //B + rev

private:
    int angleArray[4] = {60, 135, 225, 300};

    double direction;
    double primaryAngle;

    // Light light = Light();

    double lightAngle;
    lightStruct values;

    RotationController rotationController = RotationController();
    MotorController motorController = MotorController();
};


#endif
