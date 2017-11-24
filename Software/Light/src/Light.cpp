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
  dataOut[0] = 450;
  LIGHT.rxtx16(dataIn, dataOut, 1);
  Serial.println("interupted");

}

void setup(){
    Light.init();

    Serial.begin(9600);

    LIGHT.begin_SLAVE(ALT_SCK, MOSI, MISO, CS0);
    LIGHT.setCTAR_SLAVE(16, SPI_MODE0);

    pinMode(13, OUTPUT);

    // NVIC_ENABLE_IRQ(IRQ_SPI0);
    attachInterrupt(digitalPinToInterrupt(10), transfer, FALLING);
}

bool results[19];
void loop(){
    // Serial.println(Light.getAngle());
    // Light.getAngle();
    blink();
    Light.readLight();
}
