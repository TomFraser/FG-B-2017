#ifndef Config_h
#define Config_h

//Critical Stuff
#define CONST_K 3
#define CONST_J 52

//ROBOT NUM (0 is P2_bot, 1 is O_bot)
#define ROBOT O_bot

//TSOPS
#define TSOP_FORWARD_LOWER_ED 60 //Complex Orbit
#define TSOP_FORWARD_UPPER_ED 300 //Complex Orbit
//ORBIT
#define TSOP_ORBIT_FRONT_DENOMINATOR 100
#define TSOP_ORBIT_FRONT_RATIO 90
#define TSOP_ORBIT_SIDE_RATIO 50
//MOTORS
#define SPEED_VAL 70
#define FORWARD_SPEED 80
#define SPEED_ON_LINE 0
#define SPEED_OVER_LINE 60
#define SPEED_SLIDE 40

//PIXY
#define PIXY_MULTIPLIER 2
//SOLENOID
#define KICK true

//DELAY
#define MAIN_LOOP_DELAY 5

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
#define TSOP_MIN_THRESHOLD 60
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
#define COMPASS_CALIBRATION_TIME 500
#define COMPASS_CALIBRATION_NUMBER 50
#define COMPASS_MULTIPLIER 1.5
#define COMPASS_ABS_MAX 150
#define COMPASS_ABS_MAX_NEG -150

//SPI
#define DATA_LENGTH 1
#define TSOP_SS 16
#define LIGHT_SS 15
#define ALT_SCK 14

//Lightsensors
#define LIGHTSENSOR_NUM 19
#define DETECTED_NUMBER_LIGHT 3
#define NUM_COUNTBACK 2
#define ANGLE_CUTOFF 45
#define IDENTIFY_THRESHOLD 45
#define SLIDE_ANGLE 80
#define STOP_BOUND 150
#define SIDE_STOP_BOUND_MIN 135
#define SIDE_STOP_BOUND_MAX 160


//Pixy
#define CANT_SEE_GOAL 65506
#define PIXY_ABS_MAX 60 //80
#define PIXY_ABS_MAX_NEG -60 //-80

//Kicker
#define KICKER_DELAY 1000L
#define KICK_THRESHOLD 0
//Defender
#define DEFENDER_SPEED 40
#define DEFENDER_MULTIPLIER 2.30

#define P2_bot 0
#define O_bot 1

#endif
