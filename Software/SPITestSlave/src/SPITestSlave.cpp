#include <t3spi.h>
#include <Config.h>
#include <Pins.h>
#include <Arduino.h>


T3SPI SPI_SLAVE;

#define dataLength 256

volatile uint16_t data[dataLength];

volatile uint16_t returnData[dataLength];

void setup(){
  Serial.begin(9600);

  SPI_SLAVE.begin_SLAVE(ALT_SCK, MOSI, MISO, CS0);

  SPI_SLAVE.setCTAR_SLAVE(16, SPI_MODE0);

  NVIC_ENABLE_IRQ(IRQ_SPI0);

  for (int i=0; i<dataLength; i++){
    data[i] = i;
  }
}

void loop(){
  if(SPI_SLAVE.dataPointer==0 && SPI_SLAVE.packetCT==0){
    SPI_SLAVE.timeStamp1==micros();
  }

  if(SPI_SLAVE.packetCT==1){
    SPI_SLAVE.timeStamp2==micros();

    for(int i=0; i<dataLength;i++){
      Serial.println(data[0]);
    }

    SPI_SLAVE.packetCT=0;
  }
}

void spi0_isr(void){
  SPI_SLAVE.rxtx16(data, returnData, dataLength);
}
