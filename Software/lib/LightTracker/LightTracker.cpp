#include <LightTracker.h>

LightTracker::LightTracker(){
  // init
};

double LightTracker::getDirection(double lightAngle, double tsopAngle, double compassAngle){
    if(lightAngle != 65506.00){
      // if we can see the line

      // adjust the lightAngle to compass (not currently doing this cause
      // compass is spac)
      double absAngle = lightAngle + compassAngle;

      if(!wasSeeingLine){
        // just started seeing the line
        lineInitDirection = absAngle;
      }

      lastAngle = absAngle;
      wasSeeingLine = true;

      if(smallestAngleBetween(lineInitDirection, absAngle) < 90){
        // we might have moved a bit (ie maybe hit a corner or something) - set a new heading
        lineInitDirection = absAngle;
        wasSeeingLine = true;

        // need to do the fancy limit tsop angle stuff. for now just return lightAngle
        return lineInitDirection;
      }
      else{
        // flipped over the line, this is priority (adusted for compass)
        return lineInitDirection - compassAngle;
      }

    }
    else if(wasSeeingLine == true){
      // we were seeing the line and now were not
      if(smallestAngleBetween(lineInitDirection, lastAngle) < 90){
        // exited on the correct side of the line

        // reset line memeory
        wasSeeingLine = false;
        lineInitDirection = 0;

        // return tsops to just do normal game play
        return tsopAngle;
      }
      else{
        // oops, out on the wrong side - this is priority

        // dont reset line memeory cause that will get changed if we hit the
        // line

        // go back in (adjusted for compass)
        return lineInitDirection - compassAngle;

      }
    }
    else{
      // cant see line and wasnt seeing line - just to normal gameplay
      return tsopAngle;
    }
}
