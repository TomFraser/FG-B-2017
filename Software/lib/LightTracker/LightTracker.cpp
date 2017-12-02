#include <LightTracker.h>

LightTracker::LightTracker(){
  // init
}

int LightTracker::getSpeed(){
  return speed;
}

double LightTracker::getDirection(){
  return direction;
}

bool LightTracker::getSeeingLine(){
  return wasSeeingLine;
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

// Light tracker now takes in only abs directions and returns an absolute direction
void LightTracker::update(double absLight, double absMove, double moveSpeed, double absRawBall){
    if(absLight != 65506.00){
      // if we can see the line
      
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


        if(absMove == 65506.00){
          // if we dont have any directions -> just go on the line
          speed = SPEED_ON_LINE;
          direction = lineInitDirection;
        }
        else if(smallestAngleBetween(lineInitDirection, absMove) < SLIDE_ANGLE){
          // not within the angle of a slide -> just go at ball angle
          speed = moveSpeed;
          direction = absMove;
        }
        else{
          // need to decide whether to slide or to stop

          // identify whether we're on a side
          bool onSide = false;
          double angBetween = 0;

          if(smallestAngleBetween(lineInitDirection, 90) < IDENTIFY_THRESHOLD){
            // on right - from ball to move direction
            angBetween = angleBetween(absMove, lineInitDirection);
            onSide = true;

          }
          else if(smallestAngleBetween(lineInitDirection, 270) < IDENTIFY_THRESHOLD){
            // on left - from line to move direction
            angBetween = angleBetween(lineInitDirection, absMove);
            onSide = true;

          }

          if(onSide){
            if(angBetween < SIDE_STOP_BOUND_MAX && angBetween > SIDE_STOP_BOUND_MIN){
              // if within the stop area -> stop
              speed = SPEED_ON_LINE; //speed on line is stop
              direction = lineInitDirection;
            }
            else{
              // slide on slide angle
              speed = SPEED_SLIDE;
              direction = calulateBounds(absLight, absMove);
            }
          }
          else{
            // not on side -> do normal bounds
            if(smallestAngleBetween(lineInitDirection, absMove) < STOP_BOUND){
              // not within stop -> do tha slide
              speed = SPEED_SLIDE;
              direction = calulateBounds(absLight, absMove);
            }
            else{
              // stop
              speed = SPEED_ON_LINE; //speed on line is stop
              direction = lineInitDirection;
            }
          }
        }
      }
      else{
        speed = SPEED_OVER_LINE;
        // flipped over the line, this is priority (adusted for compass)
        direction = lineInitDirection;
      }
    }
    else if(wasSeeingLine == true){
      // we were seeing the line and now were not
      if(smallestAngleBetween(lineInitDirection, lastAngle) < 90){
        // exited on the correct side of the line

        // reset line memeory
        wasSeeingLine = false;
        lineInitDirection = 0;

        speed = moveSpeed;
        // return ball angle to just do normal game play
        direction = absMove;
      }
      else{
        // oops, out on the wrong side - this is priority

        // dont reset line memeory cause that will get changed if we hit the
        // line

        speed = SPEED_OVER_LINE;
        // go back in
        direction = lineInitDirection;

      }
    }
    else{
      // cant see line and wasnt seeing line - just do normal gameplay
      speed = moveSpeed;
      direction = absMove;
    }
}
