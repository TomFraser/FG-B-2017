#include <ReadTSOPS.h>
#include <Config.h>
#include <t3spi.h>

TsopController tsops;

volatile uint16_t dataIn[DATA_LENGTH];
volatile uint16_t dataOut[DATA_LENGTH];

T3SPI MOTOR;

void setup(){
    MOTOR.set_Slave(ALT_SCK, MOSI, MISO, CS0); //Might be wrong CS pin.
    MOTOR.setCTAR_SLAVE(16, SPI_MODE0);
}

void loop(){
    dataOut[0] = tsops.activateTsop();
}
