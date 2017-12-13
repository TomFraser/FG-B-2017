#include <Wire.h>
#include <Arduino.h>

#define SRF_ADDRESS         112 // Address of the SRF08
#define CMD                 (byte)0x00 // Command byte, values of 0 being sent with write have to be masked as a byte to stop them being misinterpreted as NULL this is a bug with arduino 1.0
#define RANGEBYTE           0x02 // Byte for start of ranging data
#define SRF08_I2C_TIMOUT 3000
#define I2C_STOP true



byte highByte = 0x00; // Stores high byte from ranging
byte lowByte = 0x00; // Stored low byte from ranging
uint8_t address = SRF_ADDRESS;

int getRange(){                                   // This function gets a ranging from the SRF08

  int range = 0;

  Wire.beginTransmission(SRF_ADDRESS);             // Start communticating with SRF08
  Wire.write(CMD);                                 // Send Command Byte
  Wire.write(0x51);                                // Send 0x51 to start a ranging
  Wire.endTransmission();

  delay(100);                                      // Wait for ranging to be complete

  Wire.beginTransmission(SRF_ADDRESS);             // start communicating with SRFmodule
  Wire.write(RANGEBYTE);                           // Call the register for start of ranging data
  Wire.endTransmission();

  Wire.requestFrom(SRF_ADDRESS, 2);                // Request 2 bytes from SRF module
  while(Wire.available() < 2);                     // Wait for data to arrive
  highByte = Wire.read();                          // Get high byte
  lowByte = Wire.read();                           // Get low byte

  range = (highByte << 8) + lowByte;               // Put them together

  return range;                                   // Returns Range
}

void setAddress(uint8_t newAddress){
  Wire.beginTransmission(address);
	Wire.write(CMD);
	Wire.write(0xA0);
	Wire.endTransmission();

	Wire.beginTransmission(address);
	Wire.write(CMD);
	Wire.write(0xAA);
	Wire.endTransmission();

	Wire.beginTransmission(address);
	Wire.write(CMD);
	Wire.write(0xA5);
	Wire.endTransmission();

	Wire.beginTransmission(address);
	Wire.write(CMD);
	Wire.write(newAddress);
	Wire.endTransmission();
}


void setup(){
    Serial.begin(9600);
    Wire.begin();
    delay(2000);
    Serial.println("Setip");
}

void loop(){
  int rangeData = getRange();
  Serial.println(rangeData);
}

// void setup(){
//     Serial.begin(9600);
//     Wire.begin();
//     delay(1000);
//     Serial.println("Changing");
//     setAddress(0xE2);
//
// }
//
// void loop(){
//   Serial.println("done");
//   delay(100);
// }
