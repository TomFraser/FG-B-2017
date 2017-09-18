#ifndef Config_h
#define Config_h

//Critical Stuff

//ROBOT NUM (0 is P2_bot, 1 is O_bot)
#define ROBOT O_bot

//TSOPS
#define TSOP_FORWARD_LOWER_ED 60 //Complex Orbit
#define TSOP_FORWARD_UPPER_ED 300 //Complex Orbit
//ORBIT
#define TSOP_ORBIT_FRONT_DENOMINATOR 120
#define TSOP_ORBIT_FRONT_RATIO 90
#define TSOP_ORBIT_SIDE_RATIO 65
//MOTORS
#define SPEED_VAL 60
#define SPEED_ON_LINE 0
#define SPEED_OVER_LINE 40
#define SPEED_SLIDE 40

//PIXY
#define PIXY_MULTIPLIER 2
//SOLENOID
#define KICK false
//DELAY
#define MAIN_LOOP_DELAY 0

//----------------------------------------------------------------------------

//Tsops
#define TSOP_NUM 12
#define READ_THRESHOLD 40
#define TSOP_NUM 12
#define MAX_READS 512
#define TSOP_FORWARD_LOWER 60 //Simple Orbit
#define TSOP_FORWARD_UPPER 300 //Simple Orbit
#define TSOP_ORBIT_ANGLE 45
#define TSOP_ORBIT_ANGLE_15 10
#define TSOP_MIN_THRESHOLD 110
#define TSOP_VARIABLE_ANGLE 18
#define TSOP_MIN_VAL_INDEX 180 //THIS ONE TO ORBIT CLOSE

//Strength scaling
#define TSOP_K1 12
#define TSOP_K2 2
#define TSOP_K3 1
#define MED_STRENGTH 100
#define HIGH_STRENGTH 150

//Debug
#define DEBUG true

//Motors
#define SS_MULTIPLIER 1.00

//Compass
#define COMPASS_CALIBRATION_TIME 2000
#define COMPASS_CALIBRATION_NUMBER 50
#define COMPASS_MULTIPLIER 1.5
#define COMPASS_ABS_MAX 60
#define COMPASS_ABS_MAX_NEG -60

//SPI
#define DATA_LENGTH 1
#define TSOP_SS 16
#define LIGHT_SS 15
#define ALT_SCK 14

//Lightsensors
#define LIGHTSENSOR_NUM 19
#define DETECTED_NUMBER_LIGHT 3
#define NUM_COUNTBACK 2
#define LIGHT_BOUND1 60
#define LIGHT_BOUND2 120

//Pixy
#define CANT_SEE_GOAL 65506
#define PIXY_ABS_MAX 60 //80
#define PIXY_ABS_MAX_NEG -60 //-80

//Kicker
#define KICKER_DELAY 1000L
#define LIGHTGATE_THRESHOLD 250

//Defender
#define DEFENDER_SPEED 40
#define DEFENDER_MULTIPLIER 2.30

#define P2_bot 0
#define O_bot 1

#endif
