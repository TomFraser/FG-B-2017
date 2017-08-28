#include <LightTracker.h>

LightTracker::LightTracker(){
  // init
};

double LightTracker::getDirection(double lightAngle, double tsopAngle, double compassAngle){
    // adjust the lightAngle to compass
    double absAngle = lightAngle + compassAngle;
    return absAngle;
}
