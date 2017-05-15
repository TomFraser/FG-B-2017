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
    // Serial.begin(9600);
    LIGHT.begin_SLAVE(ALT_SCK, MOSI, MISO, CS0);
    LIGHT.setCTAR_SLAVE(16, SPI_MODE0);

    NVIC_ENABLE_IRQ(IRQ_SPI0);
}

void loop(){
    // Light.readLight();
    // Serial.println(Light.getVals());
    // lightAngle = Light.getDirection();
    // dataOut[0] = lightAngle;
    dataOut[0] = 100;
}

void spi0_isr(){
    LIGHT.rxtx16(dataIn, dataOut, DATA_LENGTH);
}
