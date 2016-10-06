#include <Config.h>
#include <MotorController.h>
#include <t3spi.h>

MotorController MOTOR;
T3SPI MOTOR;

void setup(){
    MOTOR.begin_MASTER(ALT_SCK, MOSI, MISO, CS1, CS_ActiveLOW);
    MOTOR.setCTAR(CTAR_0, 16, SPI_MODE0, LSB_FIRST, SPI_CLOCK_DIV8);
}

void loop(){
    //Recieve Data From Slave 0, Slave 1

    MOTOR.setAngle(int angle);
}
