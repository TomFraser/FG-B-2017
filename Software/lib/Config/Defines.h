#ifndef Defines_h
#define Defines_h

//=========IMU (compass) Definitions=========
#define IMU_ADDRESS 0x68
#define MAG_ADDRESS 0x0C

#define GYRO_FULL_SCALE_250_DPS 0x00
#define GYRO_FULL_SCALE_500_DPS 0x08
#define GYRO_FULL_SCALE_1000_DPS 0x10
#define GYRO_FULL_SCALE_2000_DPS 0x18

#define ACC_FULL_SCALE_2_G 0x00
#define ACC_FULL_SCALE_4_G 0x08
#define ACC_FULL_SCALE_8_G 0x10
#define ACC_FULL_SCALE_16_G 0x18

//Pixy
#define PIXY_CENTRE_X 160
#define PIXY_CENTRE_Y 100

//=================Other====================
#define angToRad 0.01745329251
#define radToAng 57.2957795131

//================Lightsensors==============
#define maxNumClusters
//CARTESIAN CO-ORDINATES
#define light1x 1.0
#define light1y 0.0

#define light2x 0.9510565162951535
#define light2y 0.3090169943749474

#define light3x 0.8090169943749475
#define light3y 0.5877852522924731

#define light4x 0.587785252292473
#define light4y 0.8090169943749475

#define light5x 0.30901699437494745
#define light5y 0.9510565162951535

#define light6x -0.30901699437494756
#define light6y 0.9510565162951535

#define light7x -0.587785252292473
#define light7y 0.8090169943749475

#define light8x -0.8090169943749473
#define light8y 0.5877852522924732

#define light9x -0.9510565162951535
#define light9y 0.3090169943749475

#define light10x -1.0
#define light10y 0.0

#define light11x -0.9510565162951536
#define light11y -0.3090169943749473

#define light12x -0.8090169943749472
#define light12y -0.5877852522924734

#define light13x -0.5877852522924732
#define light13y -0.8090169943749473

#define light14x -0.30901699437494756
#define light14y -0.9510565162951535

#define light15x 0.0
#define light15y -1.0

#define light16x 0.30901699437494723
#define light16y -0.9510565162951536

#define light17x 0.5877852522924737
#define light17y -0.809016994374947

#define light18x 0.8090169943749473
#define light18y -0.5877852522924734

#define light19x 0.9510565162951535
#define light19y -0.3090169943749476

#endif
