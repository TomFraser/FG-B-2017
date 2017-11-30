#include <ReadTSOPS.h>
#include <Config.h>
#include <Arduino.h>
#include <Config.h>
#include <Pins.h>
#include <Compass.h>
#include <Blink.h>
#include <RotationController.h>
#include <t3spi.h>

#define PRINT 0
#define camSerial Serial1

Compass compass = Compass();
RotationController rotationController = RotationController();
ReadTSOPS ball;



int recieveData[8] = {};
int data[6] = {};
//Data will be: Ball Angle, Compass Angle, Goal 1 Angle, Goal 1 Size, Goal 2 Angle, Gaal 2 Size

T3SPI TSOP;

volatile uint16_t dataIn[1] = {};
volatile uint16_t dataOut[1] = {};
volatile uint16_t sendData[8] = {};

void transfer(){
    int command = SPI0_POPR;
    //Serial.println(command);
    switch(command) {
      case 1:
        SPI0_PUSHR_SLAVE = sendData[0];
        SPI0_SR |= SPI_SR_RFDF;
        break;
      case 2:
        SPI0_PUSHR_SLAVE = sendData[1];
        SPI0_SR |= SPI_SR_RFDF;
        break;
      case 3:
        SPI0_PUSHR_SLAVE = sendData[2];
        SPI0_SR |= SPI_SR_RFDF;
        break;
      case 4:
        SPI0_PUSHR_SLAVE = sendData[3];
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
        SPI0_PUSHR_SLAVE = sendData[7];
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
  //Serial.println("c");

  //Recieve Cam Data
  while(!camSerial.available());
  camSerial.read();
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
  camSerial.read();

  //Serial.println("d");

  //Sort and Calculate Cam Data
  // ball angle
  data[0] = (recieveData[0] + recieveData[1]) == 500 ? (-30) : (ball.calculateOrbitSimple((recieveData[0] + recieveData[1]), false));
  // raw compass
  data[1] = compass.getHeading();
  // attack goal angle
  data[2] = (recieveData[2] + recieveData[3]) == 500 ||  (recieveData[2] + recieveData[3]) == 0 ? (-30) : (recieveData[2] + recieveData[3]);
  // attack goal size
  data[3] = recieveData[4];
  // defend goal angle
  data[4] = (recieveData[5] + recieveData[6]) == 500 ? (-30) : (recieveData[5] + recieveData[6]);
  // defend goal size
  data[5] = recieveData[7];

  data[6] = (recieveData[0] + recieveData[1]) == 500 ? (-30) : (recieveData[0] + recieveData[1]);
  // if(data[3] < 20){
  //   Serial.print("Size:"); Serial.println(data[3]);
  // }

  // Serial.print("Size:"); Serial.println(data[3]);
  // Serial.println(coords.calcDistance(data[3], data[2]));
  // coords.update(data[3], data[2], data[5], data[4]);
  // Serial.print("X: "); Serial.print(coords.getX()); Serial.print(" Y: "); Serial.println(coords.getY());

  //Serial.println("e");

  //Sort Data into Send Array
  sendData[0] = data[0];  //Ball
  // TURN GOAL TRACKING BACK ON               change -30 to data[2]
  sendData[1] = (rotationController.rotate(data[1], data[2], data[3]) + 180); //Rotation
  sendData[2] = (data[1] + 180); //Raw Compass
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
  sendData[7] = data[6];

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
        Serial.println(sendData[4]);
        break;
    default:
      break;
  }
  //Serial.println("g");
}  
