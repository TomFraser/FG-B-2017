#include <Config.h>
#include <DirectionController.h>
#include <t3spi.h>
#include <Kicker.h>
#include <Buzzer.h>
#include <fgbcommon.h>
#include <Motor.h>
#include <Pins.h>

Motor motorA = Motor(MOTOR_A_PWM, MOTOR_A_DIR, MOTOR_A_BRK, MOTOR_A_REV);
Motor motorB = Motor(MOTOR_B_PWM, MOTOR_B_DIR, MOTOR_B_BRK, MOTOR_B_REV);
Motor motorC = Motor(MOTOR_C_PWM, MOTOR_C_DIR, MOTOR_C_BRK, MOTOR_C_REV);
Motor motorD = Motor(MOTOR_D_PWM, MOTOR_D_DIR, MOTOR_D_BRK, MOTOR_D_REV);


// MotorController MOTOR = MotorController();
// T3SPI MASTER_TEENSY;
// Kicker kicker = Kicker();
// DirectionController direction = DirectionController();
// Buzzer buzzer = Buzzer();

double tsopAng = 0.00;

int counter = 0;

void setup(){
    pinMode(A13, OUTPUT);
    analogWriteFrequency(3, 19000);
    analogWriteFrequency(4, 19000);
    analogWriteFrequency(5, 19000);
    analogWriteFrequency(21, 19000);
    // MASTER_TEENSY.begin_MASTER(ALT_SCK, MOSI, MISO, CS1, CS_ActiveLOW);
    // MASTER_TEENSY.setCTAR(CTAR_0, 16, SPI_MODE0, LSB_FIRST, SPI_CLOCK_DIV8);
    // buzzer.readyTone();
    //
    // pinMode(13, OUTPUT);
}

void loop(){

    // direction.setPWM(255);
    // motorA.set(255);
    // motorB.set(255);
    // motorC.set(255);
    // motorD.set(255);
    analogWrite(A13, 255);
    // motorA.set(255);
    // motorB.set(255);
    // motorC.set(255);
    // motorD.set(255);
    // blinkLED();

    // kicker.kickerReady(); //Kicker
    // kicker.checkLightGate();
    // kicker.kickBall();
}
//
// void testDirection(){
//     direction.setPWM(255);
//     delay(2000);
//     direction.setPWM(-255);
//     delay(2000);
// }
//
// void blinkLED(){
//     digitalWrite(13, HIGH);
//     delay(1000);
//     digitalWrite(13, LOW);
//     delay(1000);
// }
//
// void incrementSpeed(){
//     direction.setPWM(counter);
//     delay(100);
//     counter++;
//     if(counter >= 255){
//         counter = 0;
//     }
// }
