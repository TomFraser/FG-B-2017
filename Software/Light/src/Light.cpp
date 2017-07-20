#include <t3spi.h>
#include <Config.h>
// #include <Arduino.h>
#include <Light.h>

Light Light;

T3SPI LIGHT;

volatile uint16_t dataIn[DATA_LENGTH] = {};
volatile uint16_t dataOut[DATA_LENGTH] = {};

double lightAngle;

void transfer(){
    SPI0_PUSHR_SLAVE = dataOut[0]; //Push response to SPI Coms? Maybe?
    SPI0_SR |= SPI_SR_RFDF; //Signals end of transmission?
    Serial.println("COMS");
}

void setup(){
    Light.init();

    Serial.begin(9600);
    delay(3000);
    Serial.println("end setup");
    LIGHT.begin_SLAVE(ALT_SCK, MOSI, MISO, CS0);
    LIGHT.setCTAR_SLAVE(16, SPI_MODE0);

    // NVIC_ENABLE_IRQ(IRQ_SPI0);
    attachInterrupt(digitalPinToInterrupt(10), transfer, LOW);
}

void loop(){
    Light.readLight();
    lightAngle = Light.getAngle();
    // if(lightAngle > -1){
    //   Serial.println(lightAngle);
    // }
    dataOut[0] = lightAngle;
    // Serial.println(dataOut[0]);
    // delay(20);
}

void spi0_isr(){
    // LIGHT.rxtx16(dataIn, dataOut, DATA_LENGTH);
    // Serial.println(dataOut[0]);
    //Apparently using the library itself for seting data is slow af. So we are going to send data using register commands, I have little idea how these work, plz no roast.
    SPI0_PUSHR_SLAVE = dataOut[0]; //Push response to SPI Coms? Maybe?
    SPI0_SR |= SPI_SR_RFDF; //Signals end of transmission?
    Serial.println("COMS");
}
