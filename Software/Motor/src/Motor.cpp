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
    Wire1.setDefaultTimeout(200000); // 200ms

    pinMode(A12, INPUT);

    //SPI SETUP
    pinMode(LIGHT_SS, OUTPUT);
    pinMode(TSOP_SS, OUTPUT);
    SPI.begin();
    digitalWrite(TSOP_SS, HIGH);
    digitalWrite(LIGHT_SS, HIGH);
    SPI.setSCK(ALT_SCK);
    SPI.setClockDivider(SPI_CLOCK_DIV8);
    // defender.init();

    pinMode(13, OUTPUT);
    digitalWrite(13, HIGH);
}

void loop(){
    // Serial.println("Moving");
    digitalWrite(TSOP_SS, LOW);
    delay(1);
    int tsopData = SPI.transfer16(512);
    digitalWrite(TSOP_SS, HIGH);

    delay(MAIN_LOOP_DELAY);

    digitalWrite(LIGHT_SS, LOW);
    delay(1);
    int lightData = SPI.transfer16(512);
    digitalWrite(LIGHT_SS, HIGH);

    //DEFENSE
    // Vector3D defenderGo = defender.calcDirection(response); //This method returns a 2dvector where the direction is the direction and the strength is the rotation. I didnt want to make another struct.
    // Vector3D defenderGo = defender.determineDefense(response);
    // Serial.print("Angle: ");
    // Serial.println(defenderGo.x);
    // direction.calcMotors(defenderGo.x, 0.00, defenderGo.z, defenderGo.y, response);

    double rotation = rotationController.rotate();

    Serial.println(rotation);
    // Serial.println(lightTracker.getDirection(lightData, tsopData, rotation));

    //OFFENSE
    motorController.playOffense(tsopData, 65506.00, rotation, 0.00);

    if(tsopData == 0.00 && millis() >= lastKick + 2000 && KICK == true){ //Limits kicks to 1 per second
        kicker.kickBall();
        lastKick = millis();
    }
}
