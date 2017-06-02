#ifndef Config_h
#define Config_h

//Tsops
#define TSOP_NUM 12
#define READ_THRESHOLD 40
#define TSOP_NUM 12
#define MAX_READS 512
#define TSOP_FORWARD_LOWER 90
#define TSOP_FORWARD_UPPER 270
#define TSOP_ORBIT_ANGLE 45 //Formerally 90
#define TSOP_ORBIT_ANGLE_15 10
#define TSOP_MIN_THRESHOLD 110
#define TSOP_VARIABLE_ANGLE 18

#define TSOP_MIN_VAL_INDEX 240

#define TSOP_K1 12
#define TSOP_K2 2
#define TSOP_K3 1

#define MED_STRENGTH 100
#define HIGH_STRENGTH 150

//Motors
#define SPEED_VAL 60 //It was found that 90% speed can be used accurately with this new orbit. //This is a percentage 0-100 (44 is optimum apparently)

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
#define LIGHTSENSOR_THRESHOLD 60
#define DETECTED_NUMBER_LIGHT 3

//Pixy
#define PIXY_MULTIPLIER 1.0

//Kicker
#define KICKER_DELAY 2000L
#define LIGHTGATE_THRESHOLD 100

//Defender
#define DEFENDER_SPEED 40
#define DEFENDER_MULTIPLIER 2.30

#endif
