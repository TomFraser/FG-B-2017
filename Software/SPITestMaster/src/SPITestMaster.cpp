#include <t3spi.h>
#include <Config.h>
#include <Pins.h>
#include <Arduino.h>


T3SPI SPI_MASTER;

#define dataLength 256

volatile uint16_t data[dataLength];

volatile uint16_t returnData[dataLength];

void setup(){
  Serial.begin(9600);

  pinMode(TSOP_SS, OUTPUT);

  SPI_MASTER.begin_MASTER(14, MOSI, MISO, TSOP_SS, CS_ActiveLOW);

  SPI_MASTER.setCTAR(CTAR_0, 16, SPI_MODE0, LSB_FIRST, SPI_CLOCK_DIV32);

  SPI_MASTER.enableCS(TSOP_SS, CS_ActiveLOW);

  for (int i=0; i<dataLength; i++){
    data[i] = i;
  }

  // wait for slave...
  delay(5000);
}

void loop(){
  SPI_MASTER.timeStamp1 = micros();

  for(int i=0; i<1; i++){
    SPI_MASTER.txrx16(data, returnData, dataLength, CTAR_0, TSOP_SS);
  }

  SPI_MASTER.timeStamp2 = micros();

  for(int i=0; i<dataLength; i++){
    Serial.print(returnData[i]);
    Serial.flush();
  }
  Serial.println();

  SPI_MASTER.printStatistics(dataLength);

  SPI_MASTER.packetCT = 0;
}
