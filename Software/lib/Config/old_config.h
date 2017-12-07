#ifndef old_config_h
#define old_config_h

#define P2_bot 0
#define O_bot 1

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

//Pixy
#define CANT_SEE_GOAL 65506
#define PIXY_ABS_MAX 60 //80
#define PIXY_ABS_MAX_NEG -60 //-80

//PIXY
#define PIXY_MULTIPLIER 2

//Defender
#define DEFENDER_SPEED 40
#define DEFENDER_MULTIPLIER 2.30

//TSOPS
#define TSOP_FORWARD_LOWER_ED 60 //Complex Orbit
#define TSOP_FORWARD_UPPER_ED 300 //Complex Orbit
//ORBIT
#define TSOP_ORBIT_FRONT_DENOMINATOR 100
#define TSOP_ORBIT_FRONT_RATIO 75
#define TSOP_ORBIT_SIDE_RATIO 50

//Debug
#define DEBUG true

#endif
