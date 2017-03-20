#ifndef Config_h
#define Config_h

//Tsops
#define TSOP_NUM 12
#define READ_THRESHOLD 40
#define TSOP_NUM 12
#define MAX_READS 512
#define TSOP_FORWARD_LOWER 29
#define TSOP_FORWARD_UPPER 331
#define TSOP_ORBIT_ANGLE 45 //Formerally 90
#define TSOP_MIN_THRESHOLD 30
#define TSOP_VARIABLE_ANGLE 18

#define TSOP_K1 12
#define TSOP_K2 2
#define TSOP_K3 1

#define MED_STRENGTH 100
#define HIGH_STRENGTH 150

//Motors
#define SPEED_VAL 80 //This is a percentage 0-100

//Compass
#define COMPASS_CALIBRATION_TIME 2000
#define COMPASS_CALIBRATION_NUMBER 50

//SPI
#define DATA_LENGTH 1

//Lightsensors
#define LIGHTSENSOR_NUM 19
#define LIGHTSENSOR_THRESHOLD 30
#define DETECTED_NUMBER_LIGHT 3

//Pixy

//Kicker
#define KICKER_DELAY 2000L
#define LIGHTGATE_THRESHOLD 100

#endif
