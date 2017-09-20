#include <Config.h>
#include <MotorController.h>
#include <RotationController.h>
#include <Kicker.h>
#include <Buzzer.h>
#include <fgbcommon.h>
#include <PixyI2C.h>
#include <Motor.h>
#include <Pins.h>
#include <SPI.h>
#include <LightTracker.h>
#include <Blink.h>

#if ROBOT
#define LIGHTGATE_THRESHOLD 100
#else
#define LIGHTGATE_THRESHOLD 250
#endif

volatile uint16_t dataOut[DATA_LENGTH] = {};
volatile uint16_t dataIn[DATA_LENGTH] = {};

long initialTime, currentTime, lastKick = 0;

// Defender defender = Defender();
Kicker kicker = Kicker();
LightTracker lightTracker = LightTracker();
RotationController rotationController = RotationController();
MotorController motorController = MotorController();

void setup(){
    Wire1.begin(I2C_MASTER, 0x00, I2C_PINS_29_30, I2C_PULLUP_EXT, 100000);
    Wire1.setDefaultTimeout(50000); // 200ms

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
    // defender.init();

    rotationController.init();
}

void loop(){
    delay(MAIN_LOOP_DELAY);

    //SPI Transactions
    digitalWrite(TSOP_SS, LOW);
    delayMicroseconds(200);
    int tsopData = SPI.transfer16(255);
    digitalWrite(TSOP_SS, HIGH);

    digitalWrite(LIGHT_SS, LOW);
    delayMicroseconds(200);
    int lightData = SPI.transfer16(255);
    digitalWrite(LIGHT_SS, HIGH);

    digitalWrite(TSOP_SS, LOW);
    delayMicroseconds(200);
    int rotationData = SPI.transfer16(512);
    digitalWrite(TSOP_SS, HIGH);

    //Calculating absolute rotation
    double rotation = rotationController.rotate(((rotationData-180)));
    double compass = rotationData;

    //Calulating absolute angle
    // Serial.print(lightData); Serial.print(" | "); Serial.println(tsopData);
    double finalDirecton = lightTracker.getDirection(lightData, tsopData, compass);
    int speed = lightTracker.getSpeed();

    //Moving on angle
    motorController.playOffense(finalDirecton, 65506.0, rotation, speed);

    //Checking if we can kick
    if(analogRead(A12) < LIGHTGATE_THRESHOLD && millis() >= lastKick + 2000 && KICK == true){ //Limits kicks to 1 per second
        kicker.kickBall();
        lastKick = millis();
    }
    blink();
}
