#include <Config.h>
#include <MotorController.h>
#include <t3spi.h>
#include <Kicker.h>
#include <Buzzer.h>
#include <fgbcommon.h>
#include <PixyI2C.h>
#include <Motor.h>
#include <Pins.h>
#include <LightTracker.h>
#include <Blink.h>
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
LightTracker lightTracker = LightTracker();
MotorController motorController = MotorController();
T3SPI spi;

uint16_t transaction(uint16_t command, int cs) {
    dataOut[0] = command;
    for (int i = 0; i < 5; i++) {
        spi.txrx16(dataOut, dataIn, 1, CTAR_0, cs);
    }
    return dataIn[0];
}

void setup(){
    Wire1.begin(I2C_MASTER, 0x00, I2C_PINS_29_30, I2C_PULLUP_EXT, 19200);
    Wire1.setDefaultTimeout(50000); // 200ms

    pinMode(A12, INPUT);
    pinMode(13, OUTPUT);
    //
    // //SPI SETUP
    pinMode(LIGHT_SS, OUTPUT);
    pinMode(TSOP_SS, OUTPUT);

    spi.begin_MASTER(14, MOSI, MISO, TSOP_SS, CS_ActiveLOW);
    spi.setCTAR(CTAR_0, 16, SPI_MODE0, LSB_FIRST, SPI_CLOCK_DIV16);

    spi.enableCS(TSOP_SS, CS_ActiveLOW);
    spi.enableCS(LIGHT_SS, CS_ActiveLOW);
    // defender.init();


    delay(5000);
}

void loop(){
    delay(MAIN_LOOP_DELAY);

    //SPI Transactions
    int tsopData = transaction(1, TSOP_SS);
    int rotationData = transaction(2, TSOP_SS);
    int compassData = transaction(3, TSOP_SS);
    int xData = transaction(4, TSOP_SS);
    int yData = transaction(5, TSOP_SS);
    int lightData = 65506; //transaction(255, LIGHT_SS);

    //Calculating absolute rotation
    double rotation = (rotationData - 180);
    double compass = (compassData - 180);

    //Calulating absolute angle
    double finalDirection = lightTracker.getDirection(65506, tsopData, compass);
    int speed = lightTracker.getSpeed();


    Serial.println(lightData); Serial.println(tsopData); Serial.println(rotationData); Serial.println(compassData); Serial.println(xData); Serial.println(yData); Serial.println("--------------");
    // Serial.println(finalDirection);

    //Moving on angle
    motorController.playOffense(finalDirection, 65506.0, rotation, speed);

    //Checking if we can kick
    // if(analogRead(LIGHTGATE_PIN) < KICK_THRESHOLD && millis() >= lastKick + 2000 && KICK){ //Limits kicks to 1 per second
    //     kicker.kickBall();
    //     lastKick = millis();
    // }
    blink();
}
