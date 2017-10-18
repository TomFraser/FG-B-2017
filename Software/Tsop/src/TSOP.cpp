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
int sendData[6] = {};

T3SPI TSOP;

volatile uint16_t recieveDataIn[DATA_LENGTH] = {};
volatile uint16_t recieveDataOut[DATA_LENGTH] = {};

void transfer(){
  SPI0_PUSHR_SLAVE = sendData[(SPI0_POPR-1)];
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
 }

void loop() {
  blink();
  compass.update();

  if (camSerial.available()) {
    while (camSerial.read() != 42);
    for (int i = 0; i < 8; i++) {
      while(!camSerial.available());
      recieveData[i] = camSerial.read();
    }

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

    switch(recieveData[0]){
      case 255:
        sendData[0] = 255 + recieveData[1];
      default:
        if (sendData[0] = 500){
          sendData[0] = 65506;
          break;
        }
        sendData[0] = recieveData[0];
        break;
    }

    sendData[1] = 65506; //Compass

    switch(recieveData[2]){
      case 255:
        sendData[2] = 255 + recieveData[3];
      default:
        if (sendData[2] = 500){
          sendData[2] = 65506;
          break;
        }
        sendData[2] = recieveData[2];
        break;
    }

    sendData[3] = recieveData[4];

    switch(recieveData[5]){
      case 255:
        sendData[4] = 255 + recieveData[6];
      default:
        if (sendData[4] = 500){
          sendData[4] = 65506;
          break;
        }
        sendData[4] = recieveData[5];
        break;
    }

    sendData[5] = recieveData[7];

    Serial.print(sendData[0]);
    Serial.print(" ");
    Serial.print(sendData[1]);
    Serial.print(" ");
    Serial.print(sendData[2]);
    Serial.print(" ");
    Serial.print(sendData[3]);
    Serial.print(" ");
    Serial.print(sendData[4]);
    Serial.println(sendData[5]);
  }
}
