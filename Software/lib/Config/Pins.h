#ifndef Pins_h
#define Pins_h
#include <EEPROM.h>
#include <Config.h>

//========Tsop Pins========
#define POWER_PIN_1 0
#define POWER_PIN_2 20

//========Light Pins=======
//NOTE: SENSOR 1 IS THE VERY FRONT ONE AND THEY GO CLOCKWISE AROUND
#define LIGHT_1 A1
#define LIGHT_2 A2
#define LIGHT_3 A3
#define LIGHT_4 A4
#define LIGHT_5 A5
#define LIGHT_6 A6
#define LIGHT_7 A7
#define LIGHT_8 A8
#define LIGHT_9 A9
#define LIGHT_10 A10
#define LIGHT_11 A11
#define LIGHT_12 A12
#define LIGHT_13 A13
#define LIGHT_14 A14
#define LIGHT_15 A15
#define LIGHT_16 A16
#define LIGHT_17 A17
#define LIGHT_18 A18
#define LIGHT_19 A19
#define LIGHT_20 A20

//============Kicker pins==========
#define LIGHTGATE_PIN A12
#define KICKER_PIN 9

//============Buzzer pins==========
#define BUZZER_PIN 0

#if ROBOT
//Motor Pins FOR O_BOT
#define MOTOR_A_PWM 3
#define MOTOR_B_PWM 4
#define MOTOR_C_PWM 5
#define MOTOR_D_PWM 21
//
#define MOTOR_A_DIR 6
#define MOTOR_B_DIR 7
#define MOTOR_C_DIR 8
#define MOTOR_D_DIR 22
//
#define MOTOR_A_BRK 0
#define MOTOR_B_BRK 1
#define MOTOR_C_BRK 2
#define MOTOR_D_BRK 20
//
#define MOTOR_A_REV 1
#define MOTOR_B_REV 1 //
#define MOTOR_C_REV 0 //
#define MOTOR_D_REV 1 //

#else
//Motor Pins FOR P2_BOT
#define MOTOR_A_PWM 3
#define MOTOR_B_PWM 4
#define MOTOR_C_PWM 5
#define MOTOR_D_PWM 21
//
#define MOTOR_A_DIR 6
#define MOTOR_B_DIR 7
#define MOTOR_C_DIR 8
#define MOTOR_D_DIR 22
//
#define MOTOR_A_BRK 18
#define MOTOR_B_BRK 19
#define MOTOR_C_BRK 2
#define MOTOR_D_BRK 20
//
#define MOTOR_A_REV 1
#define MOTOR_B_REV 0
#define MOTOR_C_REV 0
#define MOTOR_D_REV 1

#endif

//============LED Indicators==========
#define LED_IND_1 28
#define LED_IND_2 27
#define LED_IND_3 26
#define LED_IND_4 25

#endif
