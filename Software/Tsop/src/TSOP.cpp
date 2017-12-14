#include <ReadTSOPS.h>
#include <Config.h>
#include <Arduino.h>
#include <Config.h>
#include <Pins.h>
#include <Compass.h>
#include <Blink.h>
#include <RotationController.h>
#include <t3spi.h>
#include <SRF10.h>

#define PRINT 0
#define camSerial Serial1

Compass compass = Compass();
RotationController rotationController = RotationController();
ReadTSOPS ball;

// Sonars
#if !GOALIE
  SRF10 frontSonar(FRONT_SONAR_ADDR, byte(0x0C), byte(0x0D));
  SRF10 backSonar(BACK_SONAR_ADDR, byte(0x0C), byte(0x0D));
  SRF10 leftSonar(LEFT_SONAR_ADDR, byte(0x08), byte(0x0D));
  SRF10 rightSonar(RIGHT_SONAR_ADDR, byte(0x08), byte(0x0D));
#endif

int prevTime;

int recieveData[8] = {};
int data[6] = {};
//Data will be: Ball Angle, Compass Angle, Goal 1 Angle, Goal 1 Size, Goal 2 Angle, Gaal 2 Size

#if !GOALIE
  // sonar stuff
  int sonarCount = 0;
#endif


T3SPI TSOP;

volatile uint16_t dataIn[1] = {};
volatile uint16_t dataOut[1] = {};
volatile uint16_t sendData[9] = {};

void transfer(){
    int command = SPI0_POPR;
    //Serial.println(command);
    switch(command) {
      case 1:
        SPI0_PUSHR_SLAVE = sendData[0]; //Ball Data
        SPI0_SR |= SPI_SR_RFDF;
        break;
      case 2:
        SPI0_PUSHR_SLAVE = sendData[1]; //Rotation Data
        SPI0_SR |= SPI_SR_RFDF;
        break;
      case 3:
        SPI0_PUSHR_SLAVE = sendData[2]; //Compass Data
        SPI0_SR |= SPI_SR_RFDF;
        break;
      case 4:
        SPI0_PUSHR_SLAVE = sendData[3]; //Goal Data
        SPI0_SR |= SPI_SR_RFDF;
        break;
      case 5:
        SPI0_PUSHR_SLAVE = sendData[4];
        SPI0_SR |= SPI_SR_RFDF;
        break;
      case 6:
        SPI0_PUSHR_SLAVE = sendData[5];
        SPI0_SR |= SPI_SR_RFDF;
        break;
      case 7:
        SPI0_PUSHR_SLAVE = sendData[6];
        SPI0_SR |= SPI_SR_RFDF;
        break;
      case 8:
        SPI0_PUSHR_SLAVE = sendData[7]; //Raw Ball Angle
        SPI0_SR |= SPI_SR_RFDF;
        break;
      case 9:
        SPI0_PUSHR_SLAVE = sendData[8]; //Ball Strength
        SPI0_SR |= SPI_SR_RFDF;
        break;
      default:
        SPI0_PUSHR_SLAVE = 0;
        SPI0_SR |= SPI_SR_RFDF;
        break;
    }
}

void setup() {
  Wire.begin(I2C_MASTER, 0x00, I2C_PINS_18_19, I2C_PULLUP_EXT, 100000);
  Wire.setDefaultTimeout(50000); // 200ms

  // Sonars
  #if !GOALIE
    frontSonar.setup();
    backSonar.setup();
    leftSonar.setup();
    rightSonar.setup();
  #endif

  compass.init();
  delay(10);
  compass.calibrate();
  compass.update();

  TSOP.begin_SLAVE(ALT_SCK, MOSI, MISO, CS0);
  TSOP.setCTAR_SLAVE(16, SPI_MODE0);
  attachInterrupt(digitalPinToInterrupt(10), transfer, FALLING);


  pinMode(13, OUTPUT);

  rotationController.init();

   Serial.begin(9600);
   camSerial.begin(9600);
   while(camSerial.read() != 72);
 }

void loop() {
  // Serial.println("a");
  //Serial.println("b");
  compass.update();

  #if !GOALIE
    switch (sonarCount % 4) {
      case 0:
        frontSonar.update();
        sonarCount ++;
        break;
      case 1:
        backSonar.update();
        sonarCount ++;
        break;
      case 2:
        leftSonar.update();
        sonarCount ++;
        break;
      case 3:
        rightSonar.update();
        sonarCount ++;
        break;
    }
  #endif

  //Serial.println("c");
  if ((millis() - prevTime) > CAMERA_DATA_WAIT){
    prevTime = millis();
    //Recieve Cam Data
    while(camSerial.read() != 42);
    while(!camSerial.available());
    recieveData[0] = camSerial.read();
    while(!camSerial.available());
    recieveData[1] = camSerial.read();
    while(!camSerial.available());
    recieveData[2] = camSerial.read();
    while(!camSerial.available());
    recieveData[3] = camSerial.read();
    while(!camSerial.available());
    recieveData[4] = camSerial.read();
    while(!camSerial.available());
    recieveData[5] = camSerial.read();
    while(!camSerial.available());
    recieveData[6] = camSerial.read();
    while(!camSerial.available());
    recieveData[7] = camSerial.read();
    while(!camSerial.available());
    recieveData[8] = camSerial.read();
    while(!camSerial.available());
    camSerial.read();

    //Serial.println("d");

    //Sort and Calculate Cam Data
    // ball angle
    int ballAngle = (recieveData[0] + recieveData[1]);
    data[0] = ballAngle == 500 ? (-30) : (ball.calculateOrbitSimple((ballAngle), false));
    // attack goal angle
    data[2] = (recieveData[2] + recieveData[3]) == 500 ? (-30) : (recieveData[2] + recieveData[3]);
    // attack goal size
    data[3] = recieveData[4];
    // defend goal angle
    data[4] = (recieveData[5] + recieveData[6]) == 500 ? (-30) : (recieveData[5] + recieveData[6]);
    // defend goal size
    data[5] = recieveData[7];
    // ball strength
    data[6] = recieveData[8];
    // raw ball angle
    data[7] = ballAngle == 500 ? (-30) : (ballAngle);
  }

  //Sort Data into Send Array
  sendData[0] = data[0];  //Ball
  #if GOAL_TRACKING
    #if ATTACKING_YELLOW
      sendData[1] = (rotationController.rotate(compass.getHeading(), data[2], data[3]) + 180); //Rotation
    #else
      sendData[1] = (rotationController.rotate(compass.getHeading(), data[4], data[5]) + 180); //Rotation
    #endif
  #else
    sendData[1] = (rotationController.rotate(compass.getHeading(), -30, data[3]) + 180); //Rotation
  #endif

  sendData[2] = (compass.getHeading() + 180); //Raw Compass
  #if GOALIE
    #if ATTACKING_YELLOW
      sendData[3] = data[2]; //Attack Goal Angle
      sendData[4] = data[3]; //Attack Goal Size
      sendData[5] = data[4]; //Defend Goal Angle
      sendData[6] = data[5]; //Defend Goal Size
    #else
      sendData[3] = data[4]; //Attack Goal Angle
      sendData[4] = data[5]; //Attack Goal Size
      sendData[5] = data[2]; //Defend Goal Angle
      sendData[6] = data[3]; //Defend Goal Size
    #endif
  #else
    sendData[3] = frontSonar.getRange();
    sendData[4] = backSonar.getRange();
    sendData[5] = leftSonar.getRange();
    sendData[6] = rightSonar.getRange();

    Serial.println(leftSonar.getRange());
  #endif
  sendData[7] = data[7]; //Raw Ball Angle
  sendData[8] = data[6]; //Ball Strength

  //Serial.println(data[1]);

  //Testing SPI Array
  // sendData[0] = 50; //Ball
  // sendData[1] = 100; //Rotation
  // sendData[2] = 150; //Raw Compass
  // sendData[3] = 200; //X Coordinate
  // sendData[4] = 250; //Y Coordinate
  // sendData[5] = 300;
  // sendData[6] = 350;
  // sendData[7] = 400;

  switch(PRINT){
    case 1:
      Serial.print(recieveData[0]);
      Serial.print(", ");
      Serial.print(recieveData[1]);
      Serial.print(", ");
      Serial.print(recieveData[2]);
      Serial.print(", ");
      Serial.print(recieveData[3]);
      Serial.print(", ");
      Serial.print(recieveData[4]);
      Serial.print(", ");
      Serial.print(recieveData[5]);
      Serial.print(", ");
      Serial.print(recieveData[6]);
      Serial.print(", ");
      Serial.println(recieveData[7]);
      break;
    case 2:
      Serial.print(data[0]);
      Serial.print(" ");
      Serial.print(data[1]);
      Serial.print(" ");
      Serial.print(data[2]);
      Serial.print(" ");
      Serial.print(data[3]);
      Serial.print(" ");
      Serial.print(data[4]);
      Serial.print(" ");
      Serial.println(data[5]);
      break;
    case 3:
        Serial.print(sendData[0]);
        Serial.print(" ");
        Serial.print(sendData[1]);
        Serial.print(" ");
        Serial.print(sendData[2]);
        Serial.print(" ");
        Serial.print(sendData[3]);
        Serial.print(" ");
        Serial.print(sendData[4]);
        Serial.print(" ");
        Serial.print(sendData[5]);
        Serial.print(" ");
        Serial.print(sendData[6]);
        Serial.print(" ");
        Serial.print(sendData[7]);
        Serial.print(" ");
        Serial.println(sendData[8]);
        break;
    default:
      break;
  }
  //Serial.println("g");
}  
