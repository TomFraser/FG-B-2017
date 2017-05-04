#include <t3spi.h>
#include <Config.h>
#include <Arduino.h>
#include <Light.h>

Light Light;

T3SPI LIGHT;

volatile uint16_t dataIn[DATA_LENGTH] = {};
volatile uint16_t dataOut[DATA_LENGTH] = {};

double lightAngle;

void setup(){
    Light.init();
    Serial.begin(9600);

    LIGHT.begin_SLAVE(ALT_SCK, MOSI, MISO, CS0);
    LIGHT.setCTAR_SLAVE(16, SPI_MODE0);
    NVIC_ENABLE_IRQ(IRQ_SPI0);
}

void loop(){
    Light.readLight();
    lightAngle = Light.getAngle();

    dataOut[0] = lightAngle;
    // dataOut[0] = 100;
}

void spi0_isr(){ //SPI INTERUPT
    int response = SPI0_POPR;
    switch(response){
        case 0: SPI0_PUSHR_SLAVE = 0; //Return no line
        case 1: SPI0_PUSHR_SLAVE = dataOut[0]; //Return line
        default: SPI0_PUSHR_SLAVE = dataOut[0]; //Default
    }
    // SPI0_PUSHR_SLAVE = dataOut[0];
    SPI0_SR |= SPI_SR_RFDF; //Force Refresh of SPI register?
}
