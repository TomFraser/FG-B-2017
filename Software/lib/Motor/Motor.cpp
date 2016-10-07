#include <Motor.h>

Motor::Motor(int pwm, int dir, int brk, int rev){
    pinMode(pwm, OUTPUT);
    pinMode(dir, OUTPUT);
    pinMode(brk, OUTPUT);
    reversed = rev;
    r_pwm = pwm;
    r_dir = dir;
    r_brk = brk;
}
void Motor::set(int pwm){
    digitalWrite(r_dir, pwm > 0 ? !reversed : reversed);
    analogWrite(r_pwm, pwm > 0 ? pwm : -pwm);
    digitalWrite(r_brk, LOW);
}
void Motor::brake(){
    digitalWrite(r_dir, LOW);
    analogWrite(r_pwm, 0);
    digitalWrite(r_brk, HIGH);
}
