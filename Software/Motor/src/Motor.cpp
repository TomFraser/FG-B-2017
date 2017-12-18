#include <Config.h>
#include <MotorController.h>
#include <SPI.h>
#include <Kicker.h>
#include <Buzzer.h>
#include <fgbcommon.h>
#include <PixyI2C.h>
#include <Motor.h>
#include <Pins.h>
#include <Blink.h>
#include <DirectionController.h>
#include <Goalie.h>
#include <Xbee.h>

volatile uint16_t dataOut[1] = {};
volatile uint16_t dataIn[1] = {};

bool isGoalie, isOtherConnected;
int ballX, ballY, robotX, robotY, otherBallX, otherBallY, otherRobotX, otherRobotY;

long initialTime, currentTime, lastKick = 0;

Xbees xbee = Xbees();
Kicker kicker = Kicker();
DirectionController directionController = DirectionController();
MotorController motorController = MotorController();
Goalie goalie = Goalie();

void setup(){
    xbee.init();
    isGoalie = GOALIE;
    Wire1.begin(I2C_MASTER, 0x00, I2C_PINS_29_30, I2C_PULLUP_EXT, 19200);
    Wire1.setDefaultTimeout(50000);

    pinMode(A12, INPUT);
    pinMode(13, OUTPUT);
    //SPI SETUP
    pinMode(LIGHT_SS, OUTPUT);
    pinMode(TSOP_SS, OUTPUT);
    SPI.begin();
    digitalWrite(TSOP_SS, HIGH);
    digitalWrite(LIGHT_SS, HIGH);
    SPI.setSCK(ALT_SCK);
    SPI.setClockDivider(SPI_CLOCK_DIV8);
    delay(2000);
}

void loop(){
    delay(MAIN_LOOP_DELAY);

    //SPI Transactions
    digitalWrite(TSOP_SS, LOW);
    int tsopData = SPI.transfer16(3);
    digitalWrite(TSOP_SS, HIGH);

    digitalWrite(TSOP_SS, LOW);
    int rotationData = SPI.transfer16(4);
    digitalWrite(TSOP_SS, HIGH);

    digitalWrite(TSOP_SS, LOW);
    int compassData = SPI.transfer16(5);
    digitalWrite(TSOP_SS, HIGH);

    digitalWrite(TSOP_SS, LOW);
    int goalAttackAngle = SPI.transfer16(6);
    digitalWrite(TSOP_SS, HIGH);

    digitalWrite(TSOP_SS, LOW);
    int goalAttackSize = SPI.transfer16(7);
    digitalWrite(TSOP_SS, HIGH);

    digitalWrite(TSOP_SS, LOW);
    int goalDefendAngle = SPI.transfer16(8);
    digitalWrite(TSOP_SS, HIGH);

    digitalWrite(TSOP_SS, LOW);
    int goalDefendSize= SPI.transfer16(9);
    digitalWrite(TSOP_SS, HIGH);

    digitalWrite(TSOP_SS, LOW);
    int rawBallData = SPI.transfer16(1);
    digitalWrite(TSOP_SS, HIGH);

    digitalWrite(TSOP_SS, LOW);
    int ballStrength = SPI.transfer16(2);
    digitalWrite(TSOP_SS, HIGH);
    delayMicroseconds(500);

    digitalWrite(LIGHT_SS, LOW);
    int lightData = SPI.transfer16(1);
    digitalWrite(LIGHT_SS, HIGH);

    digitalWrite(LIGHT_SS, LOW);
    int lightNumData = SPI.transfer16(2);
    digitalWrite(LIGHT_SS, HIGH);

    //Calculating absolute rotation
    double rotation = (rotationData - 180);
    double compass = (compassData - 180);

    // Serial.print(lightData); Serial.print(" | "); Serial.println(lightNumData);

    // Serial.println(tsopData); Serial.println(rotationData); Serial.println(compassData); Serial.println(goalAttackAngle); Serial.println(goalAttackSize); Serial.println(goalDefendAngle); Serial.println(goalDefendSize); Serial.println(ballStrength); Serial.println(lightData); Serial.println();

    // update the direction controller with everything it needs -> it know knows everything required to do everything
    directionController.updateGameData(tsopData, rawBallData, ballStrength, lightData, lightNumData, compass, isGoalie);
    // directionController.updateGameData(65506, 65506, 0, lightData, lightNumData, compass, isGoalie);
    // directionController.updateGameData(65506, 65506, 0, 65506, lightNumData, compass, isGoalie);


    if(isGoalie){
      directionController.updateGoalData(goalAttackSize, goalAttackAngle, goalDefendSize, goalDefendAngle);
    }
    else{
      directionController.updateGoalData(goalAttackSize, goalAttackAngle, goalDefendSize, goalDefendAngle);
    }
    // directionController.updateGoalData(65506, 65506, goalDefendSize, goalDefendAngle);
    // directionController.updateGoalData(goalAttackSize, goalAttackAngle, 0, 65506);
    // directionController.updateGoalData(0, 65506, 0, 65506);

    Serial.print(goalAttackSize); Serial.print(" | "); Serial.println(goalAttackAngle);
    Serial.print(goalDefendSize); Serial.print(" | "); Serial.println(goalDefendAngle);
    Serial.println();

    // Serial.println(rawBallData);
    // Serial.println(ballStrength);
    // Serial.print(directionController.getX()); Serial.print(" ");
    // Serial.print(directionController.getY()); Serial.print(" | ");
    // Serial.print(directionController.getBallX()); Serial.print(" ");
    // Serial.print(directionController.getBallY()); Serial.println();


    if(isGoalie){
        // ---------------- GOALIE MAIN LOGIC -----------------------
        directionController.calculateGoalie();

        motorController.move(directionController.getDirection(), rotation, directionController.getSpeed(), false);

    }else{
        // -------------------- ATTACKER MAIN LOGIC -------------------

        directionController.calculateAttack();
        motorController.move(directionController.getDirection(), rotation, directionController.getSpeed(), directionController.getFollowingBall());

        // Serial.print(tsopData); Serial.print(" | "); Serial.print(rawBallData); Serial.print(" | "); Serial.print(lightData); Serial.print(" | "); Serial.print(directionController.getDirection()); Serial.print(" | "); Serial.println(directionController.getSpeed());
        // Serial.print(compass); Serial.print(" | "); Serial.println(rotation);

    }

    //Checking if we can kick
    #if ROBOT
      // o_bot
      // Serial.println(analogRead(LIGHTGATE_PIN));
      // if(analogRead(LIGHTGATE_PIN) < KICK_THRESHOLD && millis() >= lastKick + 2000 && KICK){ //Limits kicks to 1 per second
      //     kicker.kickBall();
      //     lastKick = millis();
      // }
      if(ballStrength < KICK_THRESHOLD && ballStrength != 0 && millis() >= lastKick + 2000 && KICK){ //Limits kicks to 1 per second
          kicker.kickBall();
          lastKick = millis();
      }
    #else
      // p2_bot
      // Serial.println(ballStrength);
      if(ballStrength < KICK_THRESHOLD && ballStrength != 0 && millis() >= lastKick + 2000 && KICK){ //Limits kicks to 1 per second
          kicker.kickBall();
          lastKick = millis();
      }
    #endif

    #if XBEE_ENABLE
        isOtherConnected = xbee.updateCoordData(directionController.getBallX(), directionController.getBallY(), directionController.getX(), directionController.getY(), directionController.getBallX() != 65506 ? 1 : 0, directionController.getX() != 65506 ? 1 : 0);

        if(!isOtherConnected){
            isGoalie = DEFAULT_GOALIE;
        }else{
            isGoalie = GOALIE;
        }

        //Other robot can see ball and knows where it is
        directionController.updateOtherData(xbee.otherBallX, xbee.otherBallY, xbee.otherX, xbee.otherY, xbee.otherCanSeeBall == 1 ? true : false, xbee.otherKnowsOwnCoords == 1 ? true : false);

        // Serial.print(isOtherConnected); Serial.print(" | ");
        // Serial.print(xbee.otherBallX); Serial.print(" | ");
        // Serial.println(xbee.otherBallY);
        // Serial.println(xbee.otherCanSeeBall == 1 ? true : false);
        // Serial.println();
    #endif
}
