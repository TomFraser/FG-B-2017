#include <ReadTSOPS.h>
#include <Config.h>
#include <t3spi.h>

ReadTSOPS tsops;

volatile uint16_t dataIn[DATA_LENGTH];
volatile uint16_t dataOut[DATA_LENGTH];

T3SPI TSOP;

void setup(){
    TSOP.begin_SLAVE(ALT_SCK, MOSI, MISO, CS0); //Might be wrong CS pin.
    TSOP.setCTAR_SLAVE(16, SPI_MODE0);
}

void loop(){
    dataOut[0] = tsops.moveTangent();
}

void spi0_isr(){
    TSOP.tx16(dataOut, DATA_LENGTH);
}
