//This libraries job is to play the defender role for P2_bot (Maybe, concept codes)
#include <Arduino.h>
#include <Config.h>
#include <Pins.h>
#include <Defines.h>

#include <math.h>
#include <PixyI2C.h>
#include <Compass.h>
#include <Motor.h>
#include <Kicker.h>
#include <Vector3D.h>

//What we need -> Pixy, Compass, Motors, Kicker, Lightgate, TSOPs, Lightsensors
//What is controlled on master -> Pixy, Compass, Motors, Kicker, Lightgate

//<-- External -->
//What we need from TSOPs -> ball angle will do (without orbit)
//What we need from Lighsensors -> stay in angle will do

//<-- In Library -->
//What we need from Pixy -> Distance (Pixels to centre of pixy vision) && Scale
//What we need from Compass -> Degrees distance from centre (not remaining forward)
//What we need from Motors -> Rotating to always face the ball
//What we need from Kicker -> Kicking ball out of zone
//What we need from Lightgate -> Detect the ball


class Defender{
public:
    bool init();
    Vect2D getPixy();
    double aimBall(int angle);
    Vect2D calcScale();
    Vect2D calcDirection(int angle);
    Vect2D calcVector(Vect2D X, Vect2D Y, double rotation);

    double getCompassGlobal(); //Global compass
private:
    double getCompass(); //Read compass
    PixyI2C pixy;
    pixyData initial;
    Vect2D nothing = {0,0};
    Compass compass = Compass();
};
