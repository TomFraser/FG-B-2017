#include <ReadTSOPS.h>
#include <Config.h>
#include <t3spi.h>

ReadTSOPS tsops; //= ReadTSOPS();

T3SPI MOTOR;

void setup(){
    MOTOR.set_Slave(ALT_SCK, MOSI, MISO, CS0); //Might be wrong CS pin.
    MOTOR.setCTAR_SLAVE(16, SPI_MODE0);
}

void loop(){

}
