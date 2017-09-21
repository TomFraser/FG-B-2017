#include <ReadTSOPS.h>
#include <Config.h>
#include <Arduino.h>
#include <Config.h>
#include <Pins.h>
#include <Compass.h>
#include <Blink.h>


#include <t3spi.h>

Compass compass = Compass();

ReadTSOPS tsops;

T3SPI TSOP;

volatile uint16_t dataIn[DATA_LENGTH] = {};
volatile uint16_t dataOut[2] = {};

void transfer(){
        SPI0_PUSHR_SLAVE = (compass.getHeading()+180);
        SPI0_SR |= SPI_SR_RFDF;
}

void setup(){

    Wire.begin(I2C_MASTER, 0x00, I2C_PINS_18_19, I2C_PULLUP_EXT, 100000);
    Wire.setDefaultTimeout(50000); // 200ms

    compass.init();
    delay(10);
    compass.calibrate();
    compass.update();

    TSOP.begin_SLAVE(ALT_SCK, MOSI, MISO, CS0);
    TSOP.setCTAR_SLAVE(16, SPI_MODE0);
    attachInterrupt(digitalPinToInterrupt(10), transfer, LOW);

    pinMode(13, OUTPUT);
}

void loop(){
    compass.update();
    blink();
}
