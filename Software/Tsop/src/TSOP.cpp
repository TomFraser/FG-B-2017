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

Compass compass = Compass();
RotationController rotationController = RotationController();
ReadTSOPS ball;

#define camSerial Serial1

int recieveData[8] = {};
int data[4] = {};
//Data will be: Ball Angle, Compass Angle, Goal 1 Angle, Goal 1 Size, Goal 2 Angle, Gaal 2 Size

T3SPI spi;

volatile uint16_t dataIn[1] = {};
volatile uint16_t dataOut[1] = {};
volatile uint16_t sendData[6] = {};

void setup() {
  Wire.begin(I2C_MASTER, 0x00, I2C_PINS_18_19, I2C_PULLUP_EXT, 100000);
  Wire.setDefaultTimeout(50000); // 200ms

  compass.init();
  delay(10);
  compass.calibrate();
  compass.update();

  spi.begin_SLAVE(ALT_SCK, MOSI, MISO, CS0);
  spi.setCTAR_SLAVE(16, SPI_MODE0);

  NVIC_ENABLE_IRQ(IRQ_SPI0);



  pinMode(13, OUTPUT);

  rotationController.init();

   Serial.begin(9600);
   camSerial.begin(9600);
   while(camSerial.read() != 72);
 }

void loop() {
  blink();
  compass.update();

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

  data[0] = (recieveData[0] + recieveData[1]) == 500 ? (-30) : (recieveData[0] + recieveData[1]);
  data[1] = compass.getHeading(); //Compass
  data[2] = (recieveData[2] + recieveData[3]) == 500 ? (-30) : (recieveData[2] + recieveData[3]);
  data[3] = recieveData[4];
  data[4] = (recieveData[5] + recieveData[6]) == 500 ? (-30) : (recieveData[5] + recieveData[6]);
  data[5] = recieveData[7];

  sendData[0] = ball.calculateOrbitSimple(data[0], false);
  sendData[1] = rotationController.rotate(data[1], data[2], data[3]); //Rotation
  sendData[2] = 0; //X Coordinate
  sendData[3] = 0; //Y Coordinate

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
      Serial.println(data[1]);
      Serial.print(" ");
      Serial.print(data[2]);
      Serial.print(" ");
      Serial.print(data[3]);
      Serial.print(" ");
      Serial.print(data[4]);
      Serial.print(" ");
      Serial.println(data[5]);
      break;
    default:
      break;
  }
}  

void spi0_isr() {
    spi.rxtx16(dataIn, dataOut, 1);
    int command = dataIn[0];

    switch (command) {
        case 1:
            dataOut[0] = sendData[0];
            break;

        case 2:
            dataOut[0] = sendData[1];
            break;

        case 3:
            dataOut[0] = sendData[2];
            break;

        case 4:
            dataOut[0] = sendData[3];
            break;

        default:
            dataOut[0] = 0;
            break;
    }
}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    
