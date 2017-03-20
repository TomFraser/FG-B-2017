#include <ReadTSOPS.h>
#include <Config.h>
#include <t3spi.h>
#include <Arduino.h>
#include <Config.h>
#include <Pins.h>

ReadTSOPS tsops;
//
volatile uint16_t dataIn[DATA_LENGTH] = {};
volatile uint16_t dataOut[DATA_LENGTH] = {};

T3SPI TSOP;

void setup(){
    TSOP.begin_SLAVE(ALT_SCK, MOSI, MISO, CS0);
    TSOP.setCTAR_SLAVE(16, SPI_MODE0);
    NVIC_ENABLE_IRQ(IRQ_SPI0);
}

void loop(){
    dataOut[0] = tsops.moveTangent();
    // Serial.println(dataOut[0]);
}

void spi0_isr(){
    TSOP.rxtx16(dataIn, dataOut, DATA_LENGTH);
}
