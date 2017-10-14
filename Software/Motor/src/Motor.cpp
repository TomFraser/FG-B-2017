#include <Config.h>
#include <MotorController.h>
// #include <RotationController.h>
#include <Kicker.h>
#include <Buzzer.h>
#include <fgbcommon.h>
#include <PixyI2C.h>
#include <Motor.h>
#include <Pins.h>
#include <SPI.h>
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

 // #define BAUD_RATE 19200
 // #define CHAR_BUF 128

// volatile uint16_t dataOut[DATA_LENGTH] = {};
// volatile uint16_t dataIn[DATA_LENGTH] = {};
//
// long initialTime, currentTime, lastKick = 0;
//
// // Defender defender = Defender();
Kicker kicker = Kicker();
LightTracker lightTracker = LightTracker();
// RotationController rotationController = RotationController();
MotorController motorController = MotorController();

// void setup(){
//     Wire1.begin(I2C_MASTER, 0x00, I2C_PINS_29_30, I2C_PULLUP_EXT, 19200);
//     Wire1.setDefaultTimeout(50000); // 200ms
//
//     // pinMode(A12, INPUT);
//     // pinMode(13, OUTPUT);
//     //
//     // //SPI SETUP
//     // pinMode(LIGHT_SS, OUTPUT);
//     // pinMode(TSOP_SS, OUTPUT);
//     // SPI.begin();
//     // digitalWrite(TSOP_SS, HIGH);
//     // digitalWrite(LIGHT_SS, HIGH);
//     // SPI.setSCK(ALT_SCK);
//     // SPI.setClockDivider(SPI_CLOCK_DIV8);
//     // defender.init();
//
//     // rotationController.init();
//     delay(5000);
// }
//
// void loop(){
//     // delay(MAIN_LOOP_DELAY);
//     //
//     // //SPI Transactions
//     // digitalWrite(TSOP_SS, LOW);
//     // delayMicroseconds(200);
//     // int tsopData = SPI.transfer16(255);
//     // digitalWrite(TSOP_SS, HIGH);
//     //
//     // digitalWrite(LIGHT_SS, LOW);
//     // delayMicroseconds(200);
//     // int lightData = SPI.transfer16(255);
//     // digitalWrite(LIGHT_SS, HIGH);
//     //
//     // digitalWrite(TSOP_SS, LOW);
//     // delayMicroseconds(200);
//     // int rotationData = SPI.transfer16(512);
//     // digitalWrite(TSOP_SS, HIGH);
//     // //Calculating absolute rotation
//     // double rotation = rotationController.rotate(((rotationData-180)));
//     // double compass = (rotationData-180);
//     //
//     // //Calulating absolute angle
//     // double finalDirection = lightTracker.getDirection(lightData, tsopData, compass);
//     // int speed = lightTracker.getSpeed();
//     //
//     // // Serial.print(lightData); Serial.print(" | "); Serial.println(tsopData);
//     // // Serial.println(finalDirection);
//     //
//     // //Moving on angle
//     // motorController.playOffense(finalDirection, 65506.0, rotation, speed);
//     //
//     // //Checking if we can kick
//     // if(analogRead(LIGHTGATE_PIN) < KICK_THRESHOLD && millis() >= lastKick + 2000 && KICK){ //Limits kicks to 1 per second
//     //     kicker.kickBall();
//     //     lastKick = millis();
//     // }
//     blink();
// }

 // void setup() {
 //   Serial.begin(BAUD_RATE);
 //   Wire.begin();
 //   delay(1000); // Give the OpenMV Cam time to bootup.
 // }
 //
 // void loop() {
 //   int32_t temp = 0;
 //   char buff[CHAR_BUF] = {0};
 //
 //   Wire.requestFrom(0x12, 2);
 //   if(Wire.available() == 2) { // got length?
 //
 //     temp = Wire.read() | (Wire.read() << 8);
 //     delay(1); // Give some setup time...
 //
 //     Wire.requestFrom(0x12, temp);
 //     if(Wire.available() == temp) { // got full message?
 //
 //       temp = 0;
 //       while(Wire.available()) buff[temp++] = Wire.read();
 //
 //     } else {
 //       while(Wire.available()) Wire.read(); // Toss garbage bytes.
 //     }
 //   } else {
 //     while(Wire.available()) Wire.read(); // Toss garbage bytes.
 //   }
 //
 //   Serial.print(buff);
 //   delay(1); // Don't loop to quickly.
 // }

 #include <SPI.h>
 #define AnalogPin A2
 #define Digital1 11
 #define Digital2 12
 #define BAUD_RATE 19200
 #define CHAR_BUF 128

float angle;

 void setup() {
   Serial.begin(BAUD_RATE);
   pinMode(Digital1, INPUT);
   pinMode(Digital2, INPUT);
 }

 void loop() {
   int pinChoice = (digitalRead(Digital1) ? 1 : 0) + (digitalRead(Digital2) ? -1 : 0);
   Serial.println(pinChoice);
   switch(pinChoice){
     case 1:
        angle = analogRead(AnalogPin) * 0.1759530791788856;
        break;
     case -1:
        angle = (analogRead(AnalogPin) * 0.1759530791788856) + 180;
        break;
     case 0:
        angle = 65506;
        break;
     default:
        angle = 65506;
        break;
   }
   Serial.println(angle);
   motorController.playOffense(angle, 65506.0, 0, 50);
}
