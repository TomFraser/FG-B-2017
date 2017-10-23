#include <ReadTSOPS.h>
#include <Config.h>
#include <Arduino.h>
#include <Config.h>
#include <Pins.h>
#include <Compass.h>
#include <Blink.h>


#include <t3spi.h>

Compass compass = Compass();

ReadTSOPS tsops;

#define camSerial Serial1

int recieveData[8] = {};
//Data will be: Ball Angle, Compass Angle, Goal 1 Angle, Goal 1 Size, Goal 2 Angle, Gaal 2 Size

T3SPI TSOP;

volatile uint16_t recieveDataIn[DATA_LENGTH] = {};
volatile uint16_t recieveDataOut[DATA_LENGTH] = {};
volatile uint16_t sendData[6] = {};

void transfer(){
  SPI0_PUSHR_SLAVE = sendData[SPI0_POPR];
  SPI0_SR |= SPI_SR_RFDF;
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
  attachInterrupt(digitalPinToInterrupt(10), transfer, LOW);

  pinMode(13, OUTPUT);

   Serial.begin(9600);
   camSerial.begin(9600);
   while(camSerial.read() != 72);
 }

void loop() {
  blink();
  compass.update();

  if (camSerial.available()) {
    camSerial.read();
    for (int i = 0; i < 8; i++) {
      while(!camSerial.available());
      recieveData[i] = camSerial.read();
    }
    camSerial.read();

//recieveData Prints
    // Serial.print(recieveData[0]);
    // Serial.print(", ");
    // Serial.print(recieveData[1]);
    // Serial.print(", ");
    // Serial.print(recieveData[2]);
    // Serial.print(", ");
    // Serial.print(recieveData[3]);
    // Serial.print(", ");
    // Serial.print(recieveData[4]);
    // Serial.print(", ");
    // Serial.print(recieveData[5]);
    // Serial.print(", ");
    // Serial.print(recieveData[6]);
    // Serial.print(", ");
    // Serial.println(recieveData[7]);

    int rotation = (recieveData[2] + recieveData[3]) == 500 ? (-30) : (recieveData[2] + recieveData[3]);
    if (rotation == -30){
      rotation = compass.getHeading() + 180;
    }
    else {
      rotation = ((rotation + 180) % 360);
    }

    sendData[0] = (recieveData[0] + recieveData[1]) == 500 ? (-30) : (recieveData[0] + recieveData[1]);
    sendData[1] = rotation; //Compass
    sendData[2] = (recieveData[2] + recieveData[3]) == 500 ? (-30) : (recieveData[2] + recieveData[3]);
    sendData[3] = recieveData[4];
    sendData[4] = (recieveData[5] + recieveData[6]) == 500 ? (-30) : (recieveData[5] + recieveData[6]);
    sendData[5] = recieveData[7];

    // Serial.print(sendData[0]);
    // Serial.print(" ");
    // Serial.println(sendData[1]);
    // Serial.print(" ");
    // Serial.print(sendData[2]);
    // Serial.print(" ");
    // Serial.print(sendData[3]);
    // Serial.print(" ");
    // Serial.print(sendData[4]);
    // Serial.print(" ");
    // Serial.println(sendData[5]);
  }
}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      
