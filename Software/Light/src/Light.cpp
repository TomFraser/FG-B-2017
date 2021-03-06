#include <t3spi.h>
#include <Config.h>
#include <Arduino.h>
#include <Light.h>
#include <Blink.h>

Light Light;

T3SPI LIGHT;

volatile uint16_t dataIn[DATA_LENGTH] = {};
volatile uint16_t dataOut[DATA_LENGTH] = {};

double lightAngle;

void transfer(){
  dataOut[0] = Light.getAngle();
  SPI0_PUSHR_SLAVE = dataOut[0]; //Push response to SPI Coms? Maybe?
  SPI0_SR |= SPI_SR_RFDF; //Signals end of transmission?
}

void setup(){
    Light.init();

    Serial.begin(9600);

    LIGHT.begin_SLAVE(ALT_SCK, MOSI, MISO, CS0);
    LIGHT.setCTAR_SLAVE(16, SPI_MODE0);

    pinMode(13, OUTPUT);

    // NVIC_ENABLE_IRQ(IRQ_SPI0);
    attachInterrupt(digitalPinToInterrupt(10), transfer, LOW);
}

bool results[19];
void loop(){
    // Serial.println(Light.getAngle());
    // Light.getAngle();
    blink();
    Light.readLight();
}
