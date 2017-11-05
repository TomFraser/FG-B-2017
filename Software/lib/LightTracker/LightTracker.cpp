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

double LightTracker::adjustDirectionReturn(double lightAngle, double compassAngle){
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

void LightTracker::update(double lightAngle, double moveAngle, double moveSpeed, bool isBallAngle, double compassAngle){
    // adjust move angle
    double absMove;
    if(isBallAngle){ // ball angle is relative to robot rotation but all other directions are abs
      double absMove = mod(moveAngle - compassAngle, 360);
    }
    else{
      double absMove = moveAngle;
    }

    if(lightAngle != 65506.00){
      // if we can see the line

      // changing over ballAngle to move angle

      // adjust the lightAngle to compass
      double absLight = mod(lightAngle - compassAngle, 360);

      // Serial.println(absMove);
      // Serial.println(smallestAngleBetween(absLight, absMove));
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


        if(moveAngle == 65506.00){
          // if we dont have any directions -> just go on the line
          speed = SPEED_ON_LINE;
          direction = adjustDirectionReturn(lineInitDirection, compassAngle);
        }
        else if(smallestAngleBetween(lineInitDirection, absMove) < SLIDE_ANGLE){
          // not within the angle of a slide -> just go at ball angle
          speed = isBallAngle ? SPEED_VAL : moveSpeed;
          direction = adjustDirectionReturn(absMove, compassAngle);
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
              direction = adjustDirectionReturn(lineInitDirection, compassAngle);
            }
            else{
              // slide on slide angle
              speed = SPEED_SLIDE;
              direction = adjustDirectionReturn(calulateBounds(absLight, absMove), compassAngle);
            }
          }
          else{
            // not on side -> do normal bounds
            if(smallestAngleBetween(lineInitDirection, absMove) < STOP_BOUND){
              // not within stop -> do tha slide
              speed = SPEED_SLIDE;
              direction = adjustDirectionReturn(calulateBounds(absLight, absMove), compassAngle);
            }
            else{
              // stop
              speed = SPEED_ON_LINE; //speed on line is stop
              direction = adjustDirectionReturn(lineInitDirection, compassAngle);
            }
          }
        }
      }
      else{
        speed = SPEED_OVER_LINE;
        // flipped over the line, this is priority (adusted for compass)
        direction = adjustDirectionReturn(lineInitDirection, compassAngle);
      }
    }
    else if(wasSeeingLine == true){
      // we were seeing the line and now were not
      if(smallestAngleBetween(lineInitDirection, lastAngle) < 90){
        // exited on the correct side of the line

        // reset line memeory
        wasSeeingLine = false;
        lineInitDirection = 0;

        speed = isBallAngle ? SPEED_VAL : moveAngle;
        // return ball angle to just do normal game play
        direction = adjustDirectionReturn(absMove, compassAngle);
      }
      else{
        // oops, out on the wrong side - this is priority

        // dont reset line memeory cause that will get changed if we hit the
        // line

        speed = SPEED_OVER_LINE;
        // go back in
        direction = adjustDirectionReturn(lineInitDirection, compassAngle);

      }
    }
    else{
      speed = isBallAngle ? SPEED_VAL : moveSpeed;
      // cant see line and wasnt seeing line - just do normal gameplay
      direction = adjustDirectionReturn(absMove, compassAngle);
    }
}
