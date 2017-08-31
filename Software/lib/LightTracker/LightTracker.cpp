#include <LightTracker.h>

LightTracker::LightTracker(){
  // init
};

double LightTracker::getDirection(double lightAngle, double tsopAngle, double compassAngle){
    if(lightAngle != 65506.00){
      // adjust the lightAngle to compass
      double absAngle = lightAngle + compassAngle;
      return absAngle;
    }
}
