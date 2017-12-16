#ifndef Config_h
#define Config_h
#include <old_config.h>



//ROBOT NUM (0 is P2_bot, 1 is O_bot)
#define ROBOT P2_bot

//Enable Xbee Comms
#define XBEE_ENABLE false

//Attacking colour
#define ATTACKING_YELLOW false

#define SUPERTEAM true

#define ENABLE_SPIRAL true

//MOTORS
#define SPEED_VAL 80
#define FORWARD_SPEED 100
#define SPEED_ON_LINE 0
#define SPEED_OVER_LINE 60
#define SPEED_SLIDE 60

// IF CANT SEE BALL
#define COORD_SPEED_SCALE 2.5 // scaler to convert coordinate dist to speed
#define DISTANCE_CUTOFF_GOALIE 0
#define DISTANCE_CUTOFF_ATTACK 10
#define CUTOFF_SPEED_SCALE 1
#define ENABLE_PID true
#define PID_P 10
#define PID_I 0
#define PID_D 1
// Goalie
#define X_MULTIPLIER 1.25
#if SUPERTEAM
#define GOALIE_Y -275
#else
#define GOALIE_Y -65
#endif
#define GOALIE_X_RANGE 15
#define ENABLE_GOALIE_SURGE true
#define SURGE_X 10
#define SURGE_Y 30
#define SURGE_MAX_Y GOALIE_Y + SURGE_Y + 10
// #define SURGE_Y 30
// #define SURGE_MAX_Y GOALIE_Y + SURGE_Y

// attacker spiral
#define SPIRAL_RATE 1
#define SPIRAL_DIRECION_RATE 0.2
#define SPIRAL_SPEED 60
#define SPIRAL_RESET 0.1
#define SPIRAL_CONST 1000
#define SPIRAL_COORD_DIST 10
#define ENABLE_TARGET_SPIRAL true

//DELAY
#define MAIN_LOOP_DELAY 2
#define CAMERA_DATA_WAIT 20 //Time between reads of serial data

//Xbee
#define XBEESERIAL Serial1
#define XBEE_ADDED_CONST 128
#define XBEE_START_BYTE 255
#define XBEE_PACKAGE_SIZE 8

//Motors
#define SS_MULTIPLIER 1.00

//Rotation
#define COMPASS_CALIBRATION_TIME 500
#define COMPASS_CALIBRATION_NUMBER 500
#define COMPASS_MULTIPLIER 2
#define COMPASS_ABS_MAX 150
#define COMPASS_ABS_MAX_NEG -150

#define GOAL_MULTIPLIER 3.5
#define GOAL_SIZE_THRESHOLD 5

#define GOAL_TRACKING_CUTOFF 90

//SPI
#define DATA_LENGTH 1
#define TSOP_SS 16
#define LIGHT_SS 15
#define ALT_SCK 14

//Lightsensors
#define AUTO_LIGHT false
#define LIGHTSENSOR_NUM 20
#define DETECTED_NUMBER_LIGHT 3
#define THRESHOLD_OFFSET 15
#define LIGHT_CALB_LOOPS 1000
#define NUM_COUNTBACK 2
#define ANGLE_CUTOFF 75
#define IDENTIFY_THRESHOLD 45
#define SLIDE_ANGLE 80
#define STOP_BOUND 150
#define SIDE_STOP_BOUND_MIN 135
#define SIDE_STOP_BOUND_MAX 160
#define ENABLE_DEPTH false
#define DEPTH_THRESH 3
#define DEPTH_SPEED 20

//Kicker
#define KICKER_DELAY 1000L
#define KICK_THRESHOLD 0

#if ROBOT
  #include <O_bot.h>
#else
  #include <P2_bot.h>
#endif


#define CONST_K 1.75
#define CONST_J 100

#endif
