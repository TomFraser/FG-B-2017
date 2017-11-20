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

long initialTime, currentTime, lastKick = 0;

// Defender defender = Defender();
Kicker kicker = Kicker();
DirectionController directionController = DirectionController();
MotorController motorController = MotorController();
Goalie goalie = Goalie();

uint16_t transaction(uint16_t command, int cs) {
    digitalWrite(cs, LOW);
    delayMicroseconds(400);
    int data = SPI.transfer16(command);
    digitalWrite(cs, HIGH);
    return data;
}

void setup(){
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

    delay(5000);
}

void loop(){
    //delay(MAIN_LOOP_DELAY);

    //SPI Transactions
    int tsopData = transaction(1, TSOP_SS);
    // int rotationData = transaction(2, TSOP_SS);
    // int compassData = transaction(3, TSOP_SS);
    // int goalAttackAngle = transaction(4, TSOP_SS);
    // int goalAttackSize = transaction(5, TSOP_SS);
    // int goalDefendAngle = transaction(6, TSOP_SS);
    // int goalDefendSize = transaction(7, TSOP_SS);
    // int rawBallData = transaction(8, TSOP_SS);
    int rotationData = 65506;
    int compassData = 65506;
    int goalAttackAngle = 65506;
    int goalAttackSize = 65506;
    int goalDefendAngle = 65506;
    int goalDefendSize = 65506;
    int rawBallData = 65506;
    int lightData = 65506; //transaction(255, LIGHT_SS);

    // if (tsopData == 0 || rotationData == 0 || compassData == 0 || goalAttackAngle == 0 || goalAttackSize == 0 || goalDefendAngle == 0 || goalDefendSize == 0 || lightData == 0) {
    //   int tsopData = transaction(1, TSOP_SS);
    //   int rotationData = transaction(2, TSOP_SS);
    //   int compassData = transaction(3, TSOP_SS);
    //   int goalAttackAngle = transaction(4, TSOP_SS);
    //   int goalAttackSize = transaction(5, TSOP_SS);
    //   int goalDefendAngle = transaction(6, TSOP_SS);
    //   int goalDefendSize = transaction(7, TSOP_SS);
    //   int rawBallData = transaction(8, TSOP_SS);
    //   int lightData = 65506; //transaction(255, LIGHT_SS);
    // }

    //Calculating absolute rotation
    double rotation = (rotationData - 180);
    double compass = (compassData - 180);

    Serial.println(tsopData); //Serial.println(rotationData); Serial.println(compassData); Serial.println(goalAttackAngle); Serial.println();

    // update the direction controller with everything it needs -> it know knows everything required to do everything
    directionController.updateGameData(65506, lightData, compass);
    directionController.updateGoalData(goalAttackSize, goalAttackAngle, goalDefendSize, goalDefendAngle);

    #if GOALIE
    // ---------------- GOALIE MAIN LOGIC -----------------------
      goalie.calcTarget(directionController.getX(), directionController.getY(), rawBallData, goalDefendAngle, rotation);

      directionController.goToCoords(goalie.getX(), goalie.getY());

      motorController.playOffense(directionController.getDirection(), 65506.0, goalie.getGoalAngle(), directionController.getSpeed());

    #else
    // -------------------- ATTACKER MAIN LOGIC -------------------
      directionController.calulateAttack();

      motorController.playOffense(directionController.getDirection(), 65506.0, rotation, directionController.getSpeed());
    #endif

    //Checking if we can kick
    if(analogRead(LIGHTGATE_PIN) < KICK_THRESHOLD && millis() >= lastKick + 2000 && KICK){ //Limits kicks to 1 per second
        kicker.kickBall();
        lastKick = millis();
    }
    // blink();
}
