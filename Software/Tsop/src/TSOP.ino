#include <ReadTSOPS.h>
#include <Config.h>
#include <t3spi.h>
#include <Arduino.h>
#include <Config.h>
#include <Pins.h>

ReadTSOPS tsops;
//
volatile uint16_t dataIn[DATA_LENGTH];
volatile uint16_t dataOut[DATA_LENGTH];

// T3SPI TSOP;

void setup(){
    // TSOP.begin_SLAVE(ALT_SCK, MOSI, MISO, CS0); //Might be wrong CS pin.
    // TSOP.setCTAR_SLAVE(16, SPI_MODE0);
}

void loop(){
    dataOut[0] = tsops.moveTangent();
    // Serial.println(tsops.moveTangent());
    delay(100);
    // Serial.println("hey");
}

// void spi0_isr(){
//     TSOP.rxtx16(dataIn, dataOut, DATA_LENGTH);
// }
