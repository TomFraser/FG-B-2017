#include <LightTracker.h>

LightTracker::LightTracker(){
  // init
};

int LightTracker::getSpeed(){
  return speed;
}

double LightTracker::getDirection(double lightAngle, double tsopAngle, double compassAngle){
    if(lightAngle != 65506.00){
      // if we can see the line

      // adjust the lightAngle to compass (not currently doing this cause
      // compass is spac)
      // double absAngle = lightAngle + compassAngle;
      double absAngle = lightAngle;

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


        if(smallestAngleBetween(lineInitDirection, tsopAngle) < LIGHT_BOUND && tsopAngle != 65506.00){
          speed = SPEED_VAL;
          return tsopAngle;

          // this is stuff for smallestAngleBetween > LIGHT_BOUND
          // if((mod(lineInitDirection + 180, 360) - tsopAngle) > 0 && (mod(lineInitDirection + 180, 360) - tsopAngle) < 180){
          //   // need to move on upper bound
          //   return mod((lightAngle + LIGHT_BOUND), 360);
          // }
          // else{
          //   // lower bound
          //   return mod((lightAngle - LIGHT_BOUND), 360);
          // }
        }
        else{
          speed = SPEED_ON_LINE;
          return lineInitDirection;
        }
      }
      else{
        speed = SPEED_OVER_LINE;
        // flipped over the line, this is priority (adusted for compass)
        return lineInitDirection;
      }

    }
    else if(wasSeeingLine == true){
      // we were seeing the line and now were not
      if(smallestAngleBetween(lineInitDirection, lastAngle) < 90){
        // exited on the correct side of the line

        // reset line memeory
        wasSeeingLine = false;
        lineInitDirection = 0;

        speed = SPEED_VAL;
        // return tsops to just do normal game play
        return tsopAngle;
      }
      else{
        // oops, out on the wrong side - this is priority

        // dont reset line memeory cause that will get changed if we hit the
        // line

        speed = SPEED_OVER_LINE;
        // go back in (adjusted for compass)
        return lineInitDirection;

      }
    }
    else{
      speed = SPEED_VAL;
      // cant see line and wasnt seeing line - just to normal gameplay
      return tsopAngle;
    }
}
