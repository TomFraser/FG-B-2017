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
    //<-- Magical Slave Setup From the interwebs -->
    // SPCR =0x40; // |= _BV(SPE);  //From Arduino, dosn't work without it??
    // SPI0_MCR         = 0x01000400;
    // SPI0_RSER        = 0x00000000;
    // SPI0_CTAR0_SLAVE = 0x38000000; //0x11000000;
    //
    // //take clock off pin 13
    // CORE_PIN13_CONFIG = PORT_PCR_MUX(1);
    // //put clock on pun 14
    // CORE_PIN14_CONFIG = PORT_PCR_DSE | PORT_PCR_MUX(2);
    //
    // pinMode(SS, INPUT);      //Pin 10
    // pinMode(MISO, INPUT);    //Pin 12
    // pinMode(14, INPUT);      //Clock

    TSOP.begin_SLAVE(ALT_SCK, MOSI, MISO, CS0);
    TSOP.setCTAR_SLAVE(16, SPI_MODE0);
    // NVIC_ENABLE_IRQ(IRQ_SPI0);
    attachInterrupt(digitalPinToInterrupt(10), transfer, LOW);

    digitalWrite(13, HIGH); //Lets us know the teensy is ready
}

void loop(){
    // dataOut[0] = 6969;
    delay(10);
}

void spi0_isr(){ //SPI INTERUPT
    dataOut[0] = tsops.moveAngle();
    //Apparently using the library itself for seting data is slow af. So we are going to send data using register commands, I have little idea how these work, plz no roast.
    SPI0_PUSHR_SLAVE = dataOut[0]; //Push response to SPI Coms? Maybe?
    SPI0_SR |= SPI_SR_RFDF; //Signals end of transmission?
}
