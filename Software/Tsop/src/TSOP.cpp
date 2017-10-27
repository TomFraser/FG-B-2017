#include <ReadTSOPS.h>
#include <Config.h>
#include <Arduino.h>
#include <Config.h>
#include <Pins.h>
#include <Compass.h>
#include <Blink.h>
#include <RotationController.h>
#include <t3spi.h>
#include <CoordCalc.h>

#define PRINT 0
#define camSerial Serial1

Compass compass = Compass();
RotationController rotationController = RotationController();
ReadTSOPS ball;
CoordCalc coords;


int recieveData[8] = {};
int data[6] = {};
//Data will be: Ball Angle, Compass Angle, Goal 1 Angle, Goal 1 Size, Goal 2 Angle, Gaal 2 Size

T3SPI spi;

volatile uint16_t dataIn[1] = {};
volatile uint16_t dataOut[1] = {};
volatile uint16_t sendData[8] = {};

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
  //Serial.println("a");
  blink();
  //Serial.println("b");
  compass.update();
  //Serial.println("c");

  //Recieve Cam Data
  int val = camSerial.read();
  while(true){
      if (val == -1){
          val = camSerial.read();
      }else{
          break;
      }
  }
  for (int i; i < 8; i++){
      val = camSerial.read();
      while(true){
          Serial.println(val); //THIS IS REQUIRED OTHERWISE IT BREAKS
          if (val == -1){
              val = camSerial.read();
          }else{
              recieveData[i] = val;
              break;
          }
      }
  }
  val = camSerial.read();
  while(val == -1){
      val = camSerial.read();
  }

  // recieveData[0] = camSerial.read();
  // recieveData[1] = camSerial.read();
  // recieveData[2] = camSerial.read();
  // recieveData[3] = camSerial.read();
  // recieveData[4] = camSerial.read();
  // recieveData[5] = camSerial.read();
  // recieveData[6] = camSerial.read();
  // recieveData[7] = camSerial.read();
  // camSerial.read();

  //Serial.println("d");

  //Sort and Calculate Cam Data
  data[0] = (recieveData[0] + recieveData[1]) == 500 ? (-30) : (ball.calculateOrbitSimple((recieveData[0] + recieveData[1]), false)); //Ball Angle
  data[1] = compass.getHeading(); //Raw Compass
  data[2] = (recieveData[2] + recieveData[3]) == 500 ? (-30) : (recieveData[2] + recieveData[3]); //Attack Goal Angle
  data[3] = recieveData[4]; //Attack Goal Size
  data[4] = (recieveData[5] + recieveData[6]) == 500 ? (-30) : (recieveData[5] + recieveData[6]); //Defend Goal Angle
  data[5] = recieveData[7]; //Defend Goal Size

  // Serial.println(coords.calcDistance(data[3], data[2]));

  //Serial.println("e");

  //Sort Data into Send Array
  sendData[0] = data[0];  //Ball
  sendData[1] = (rotationController.rotate(data[1], data[2], data[3]) + 180); //Rotation
  sendData[2] = (data[1] + 180); //Raw Compass
  sendData[3] = 0; //X Coordinate
  sendData[4] = 0; //Y Coordinate
  sendData[5] = (recieveData[0] + recieveData[1]) == 500 ? (-30) : (recieveData[0] + recieveData[1]);
  sendData[6] = data[4];
  sendData[7] = data[5];

  //Serial.println(sendData[1]);

  //Testing SPI Array
  // sendData[0] = 50; //Ball
  // sendData[1] = 100; //Rotation
  // sendData[2] = 150; //Raw Compass
  // sendData[3] = 200; //X Coordinate
  // sendData[4] = 250; //Y Coordinate

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

void spi0_isr() {
    spi.rxtx16(dataIn, dataOut, 1);
    int command = dataIn[0];

    switch (command) {
        case 1: //Ball Angle
            dataOut[0] = (uint16_t)sendData[0];
            break;

        case 2: //Rotation
            dataOut[0] = (uint16_t)sendData[1];
            break;

        case 3: //Raw Compass
            dataOut[0] = (uint16_t)sendData[2];
            break;

        case 4: //X Coordinate
            dataOut[0] = (uint16_t)sendData[3];
            break;

        case 5: //Y Coordinate
            dataOut[0] = (uint16_t)sendData[4];
            break;

        case 6: //Raw Ball Angle
            dataOut[0] = (uint16_t)sendData[5];
            break;

        case 7: //Defend Goal Angle
            dataOut[0] = (uint16_t)sendData[6];
            break;

        case 8: //Defend Goal Size
            dataOut[0] = (uint16_t)sendData[7];
            break;

        default: //Y Coordinate
            dataOut[0] = (uint16_t)0;
            break;
    }
}
