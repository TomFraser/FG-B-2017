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

void transfer(){
    dataOut[0] = tsops.moveAngle();
    SPI0_PUSHR_SLAVE = dataOut[0]; //Push response to SPI Coms? Maybe?
    SPI0_SR |= SPI_SR_RFDF; //Signals end of transmission?
}

void setup(){

    TSOP.begin_SLAVE(ALT_SCK, MOSI, MISO, CS0);
    TSOP.setCTAR_SLAVE(16, SPI_MODE0);
    attachInterrupt(digitalPinToInterrupt(10), transfer, LOW);

    digitalWrite(13, HIGH); //Lets us know the teensy is ready
}

void loop(){
    // dataOut[0] = 6969;
    delay(10);
}
