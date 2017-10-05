#include <LightTracker.h>

LightTracker::LightTracker(){
  // init
};

int LightTracker::getSpeed(){
  return speed;
}

double LightTracker::adjustLightReturn(double lightAngle, double compassAngle){
  return mod(lightAngle + compassAngle, 360);
}

double LightTracker::calulateBounds(double lightAngle, double ballAngle){
  if((mod(lightAngle + 180, 360) - ballAngle) > 0 && (mod(lightAngle + 180, 360) - ballAngle) < 180){
    // need to move on upper bound
    return mod(lightAngle + SLIDE_ANGLE, 360);
  }
  else{
    // lower bound
    return mod(lightAngle - SLIDE_ANGLE, 360);
  }
}

double LightTracker::getDirection(double lightAngle, double ballAngle, double compassAngle){
    if(lightAngle != 65506.00){
      // if we can see the line

      // adjust the lightAngle to compass
      double absLight = mod(lightAngle - compassAngle, 360);
      double absBall = mod(ballAngle - compassAngle, 360);

      // Serial.println(absBall);
      // Serial.println(smallestAngleBetween(absLight, absBall));
      // Serial.println(compassAngle);
      // Serial.println();


      if(!wasSeeingLine){
        // just started seeing the line
        lineInitDirection = absLight;
      }

      lastAngle = absLight;
      wasSeeingLine = true;

      // CHANGE ANGLE_CUTOFF ONCE THE NEW LIGHTSENSORS COME
      if(smallestAngleBetween(lineInitDirection, absLight) < ANGLE_CUTOFF){
        // we might have moved a bit (ie maybe hit a corner or something) - set a new heading
        lineInitDirection = absLight;
        wasSeeingLine = true;


        if(ballAngle == 65506.00){
          // if we cant see the ball -> just go on the line
          speed = SPEED_ON_LINE;
          return adjustLightReturn(lineInitDirection, compassAngle);
        }
        else if(smallestAngleBetween(lineInitDirection, absBall) < SLIDE_ANGLE){
          // not within the angle of a slide -> just go at ball angle
          speed = SPEED_VAL;
          return ballAngle;
        }
        else{
          // need to decide whether to slide or to stop

          // identify whether we're on a side
          bool onSide = false;
          double angBetween = 0;

          if(smallestAngleBetween(lineInitDirection, 90) < IDENTIFY_THRESHOLD){
            // on right - from ball to line
            angBetween = angleBetween(absBall, lineInitDirection);
            onSide = true;

          }
          else if(smallestAngleBetween(lineInitDirection, 180) < IDENTIFY_THRESHOLD){
            // on left - from line to ball
            angBetween = angleBetween(lineInitDirection, absBall);
            onSide = true;

          }

          if(onSide){
            if(angBetween < SIDE_STOP_BOUND_MAX && angBetween > SIDE_STOP_BOUND_MIN){
              // if within the stop area -> stop
              speed = SPEED_ON_LINE; //speed on line is stop
              return adjustLightReturn(lineInitDirection, compassAngle);
            }
            else{
              // slide on slide angle
              speed = SPEED_SLIDE;
              return adjustLightReturn(calulateBounds(absLight, absBall), compassAngle);
            }
          }
          else{
            // not on side -> do normal bounds
            if(smallestAngleBetween(lineInitDirection, absBall) < STOP_BOUND){
              // not within stop -> do tha slide
              speed = SPEED_SLIDE;
              return adjustLightReturn(calulateBounds(absLight, absBall), compassAngle);
            }
            else{
              // stop
              speed = SPEED_ON_LINE; //speed on line is stop
              return adjustLightReturn(lineInitDirection, compassAngle);
            }
          }
        }
      }
      else{
        speed = SPEED_OVER_LINE;
        // flipped over the line, this is priority (adusted for compass)
        return adjustLightReturn(lineInitDirection, compassAngle);
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
        // return ball angle to just do normal game play
        return ballAngle;
      }
      else{
        // oops, out on the wrong side - this is priority

        // dont reset line memeory cause that will get changed if we hit the
        // line

        speed = SPEED_OVER_LINE;
        // go back in
        return adjustLightReturn(lineInitDirection, compassAngle);

      }
    }
    else{
      speed = SPEED_VAL;
      // cant see line and wasnt seeing line - just do normal gameplay
      return ballAngle;
    }
}
