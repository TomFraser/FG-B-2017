#ifndef Config_h
#define Config_h

//Tsops
#define TSOP_NUM 12
#define READ_THRESHOLD 40
#define TSOP_NUM 12
#define MAX_READS 512
#define TSOP_FORWARD_LOWER 60 //90 //THESE NEED CHANGE
#define TSOP_FORWARD_UPPER 300 //270 //THESE NEED CHANGE
#define TSOP_FORWARD_LOWER_ED 90
#define TSOP_FORWARD_UPPER_ED 270
#define TSOP_ORBIT_ANGLE 45
#define TSOP_ORBIT_ANGLE_15 10
#define TSOP_MIN_THRESHOLD 110
#define TSOP_VARIABLE_ANGLE 18

#define TSOP_MIN_VAL_INDEX 180 //THIS ONE TO ORBIT CLOSE

#define TSOP_K1 12
#define TSOP_K2 2
#define TSOP_K3 1

#define MED_STRENGTH 100
#define HIGH_STRENGTH 150

//Debug
#define DEBUG true

//Motors
#define SPEED_VAL 60
#define COME_BACK_IN_SPD 30
#define SS_MULTIPLIER 1.00

//Compass
#define COMPASS_CALIBRATION_TIME 2000
#define COMPASS_CALIBRATION_NUMBER 50
#define COMPASS_MULTIPLIER 0.85
#define COMPASS_ABS_MAX 40
#define COMPASS_ABS_MAX_NEG -40

//SPI
#define DATA_LENGTH 1

//Lightsensors
#define LIGHTSENSOR_NUM 19
#define LIGHTSENSOR_AVG 100
#define LIGHTSENSOR_THRESHOLD 80
#define DETECTED_NUMBER_LIGHT 3
#define NUM_COUNTBACK 2

//Pixy
#define PIXY_MULTIPLIER 1.0
#define CANT_SEE_GOAL 65506

//Kicker
#define KICKER_DELAY 1000L
#define LIGHTGATE_THRESHOLD 100

//Defender
#define DEFENDER_SPEED 40
#define DEFENDER_MULTIPLIER 2.30

#endif
