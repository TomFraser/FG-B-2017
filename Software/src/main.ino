#include <Compass.h>

Compass compass = Compass();

void setup(){
    compass.calibrate();
}

void loop(){
    compass.update();
    compass.getHeading();
}
