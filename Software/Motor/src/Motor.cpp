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
// #include <Xbee.h>

//
#if ROBOT
  // o_bot
  #define KICK_THRESHOLD 300
#else
  // P2_bot
  #define KICK_THRESHOLD 980
#endif

volatile uint16_t dataOut[1] = {};
volatile uint16_t dataIn[1] = {};

bool isGoalie;
int ballX, ballY, robotX, robotY, otherBallX, otherBallY, otherRobotX, otherRobotY;

long initialTime, currentTime, lastKick = 0;

// Defender defender = Defender();
// Xbees xbee = Xbees();
Kicker kicker = Kicker();
DirectionController directionController = DirectionController();
MotorController motorController = MotorController();
Goalie goalie = Goalie();

void setup(){
    isGoalie = GOALIE;
    Wire1.begin(I2C_MASTER, 0x00, I2C_PINS_29_30, I2C_PULLUP_EXT, 19200);
    Wire1.setDefaultTimeout(50000); // 200ms

    pinMode(A12, INPUT);
    pinMode(13, OUTPUT);
    //
    //SPI SETUP
    pinMode(LIGHT_SS, OUTPUT);
    pinMode(TSOP_SS, OUTPUT);
    SPI.begin();
    digitalWrite(TSOP_SS, HIGH);
    digitalWrite(LIGHT_SS, HIGH);
    SPI.setSCK(ALT_SCK);
    SPI.setClockDivider(SPI_CLOCK_DIV8);
    // defender.init();

    delay(5000);
}

void loop(){
    delay(MAIN_LOOP_DELAY);

    //SPI Transactions
    digitalWrite(13, HIGH);
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
    int goalDefendSize= SPI.transfer16(1);
    digitalWrite(TSOP_SS, HIGH);

    digitalWrite(TSOP_SS, LOW);
    int rawBallData = SPI.transfer16(2);
    digitalWrite(TSOP_SS, HIGH);
    delayMicroseconds(500);
    digitalWrite(LIGHT_SS, LOW);
    delayMicroseconds(500);
    int lightData = SPI.transfer16(255);
    digitalWrite(LIGHT_SS, HIGH);
    digitalWrite(13, LOW);

    //Calculating absolute rotation
    double rotation = (rotationData - 180);
    double compass = (compassData - 180);

    // Serial.println(tsopData); Serial.println(rotationData); Serial.println(compassData); Serial.println(goalAttackAngle); Serial.println(goalAttackSize); Serial.println(goalDefendAngle); Serial.println(goalDefendSize); Serial.println(rawBallData); Serial.println(lightData); Serial.println();

    // update the direction controller with everything it needs -> it know knows everything required to do everything
    directionController.updateGameData(tsopData, lightData, compass);
    directionController.updateGoalData(goalAttackSize, goalAttackAngle, goalDefendSize, goalDefendAngle);
    // directionController.updateGoalData(0, 65506, 0, 65506);
    // directionController.updateGoalData(goalAttackSize, goalAttackAngle, 0, 65506);

    // Serial.print(goalAttackSize); Serial.print(" | "); Serial.println(goalAttackAngle);
    // Serial.print(goalDefendSize); Serial.print(" | "); Serial.println(goalDefendAngle);
    // Serial.println();

    if(isGoalie){

        // ---------------- GOALIE MAIN LOGIC -----------------------
        goalie.calcTarget(directionController.getX(), directionController.getY(), rawBallData, goalDefendAngle, rotation);

        directionController.goToCoords(goalie.getX(), goalie.getY());

        motorController.playOffense(directionController.getDirection(), 65506.0, goalie.getGoalAngle(), directionController.getSpeed());

    }else{
        // -------------------- ATTACKER MAIN LOGIC -------------------

        // Serial.print(directionController.getX()); Serial.print(" ");
        // Serial.println(directionController.getY());
        // Serial.println();

        directionController.calulateAttack();
        motorController.playOffense(directionController.getDirection(), 65506.0, rotation, directionController.getSpeed());
    }
    // -------------------- ATTACKER MAIN LOGIC -------------------
      // Serial.println(rawBallData);
      // Serial.print(directionController.getX()); Serial.print(" ");
      // Serial.println(directionController.getY());
      // Serial.println();

      // Serial.print(goalAttackSize); Serial.print(" "); Serial.println(goalAttackAngle);
      // Serial.print(goalDefendSize); Serial.print(" "); Serial.println(goalDefendAngle);
      // Serial.println();



    //Checking if we can kick
    if(analogRead(LIGHTGATE_PIN) < KICK_THRESHOLD && millis() >= lastKick + 2000 && KICK){ //Limits kicks to 1 per second
        kicker.kickBall();
        lastKick = millis();
    }

    // if(xbee.connected()){
    //     xbee.updateCoordData(ballX, ballY, robotX, robotY);
    //     otherBallX = xbee.otherBallX;
    //     otherBallY = xbee.otherBallY;
    //     otherRobotX = xbee.otherX;
    //     otherRobotY = xbee.otherY;
    // }else{
    //     goalie = true;
    // }
}
