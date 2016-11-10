#ifndef Motor_h
#define Motor_h

// #include <Config.h>
// #include <Pins.h>
// #include <Defines.h>
#include <Arduino.h>

class Motor{

public:
    Motor(int pwm, int dir, int brk, int rev);

    //Set a pwm value to the motor
    void set(int pwm);
    //Stop the motor with no coast
    void brake();

private:
    int r_brk;
    int r_pwm;
    int r_dir;
    int reversed;
};

#endif
