#include <t3spi.h>
//

T3SPI LIGHT;

void setup(){
    LIGHT.begin_SLAVE(ALT_SCK, MOSI, MISO, CS1); //Might be wrong CS pin.
    LIGHT.setCTAR_SLAVE(16, SPI_MODE0);
}

void loop(){

}
