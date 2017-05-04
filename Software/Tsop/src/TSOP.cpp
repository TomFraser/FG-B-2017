#include <ReadTSOPS.h>
#include <Config.h>
#include <Arduino.h>
#include <Config.h>
#include <Pins.h>

#include <t3spi.h>

ReadTSOPS tsops;

T3SPI TSOP;

volatile uint16_t dataIn[DATA_LENGTH] = {};
volatile uint16_t dataOut[DATA_LENGTH] = {};

void setup(){
    TSOP.begin_SLAVE(ALT_SCK, MOSI, MISO, CS0);
    TSOP.setCTAR_SLAVE(16, SPI_MODE0);
    NVIC_ENABLE_IRQ(IRQ_SPI0);
}

void loop(){
    // dataOut[0] = tsops.moveTangent();
    dataOut[0] = 6969;
    delay(10);
}

void spi0_isr(){ //SPI INTERUPT
    int request = SPI0_POPR;
    switch(request){
        case 0: SPI0_PUSHR_SLAVE = -30; //Return no ball
        case 1: SPI0_PUSHR_SLAVE = dataOut[0]; //Return ball
        default: SPI0_PUSHR_SLAVE = dataOut[0]; //Default
    }
    // SPI0_PUSHR_SLAVE = dataOut[0];
    SPI0_SR |= SPI_SR_RFDF; //Force Refresh of SPI register?
}
