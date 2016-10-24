#include <Config.h>
#include <DirectionController.h>
#include <t3spi.h>
#include <Motor.h>

// MotorController MOTOR = MotorController();
T3SPI MASTER_TEENSY;

int angle = 0;

void setup(){
    MASTER_TEENSY.begin_MASTER(ALT_SCK, MOSI, MISO, CS1, CS_ActiveLOW);
    MASTER_TEENSY.setCTAR(CTAR_0, 16, SPI_MODE0, LSB_FIRST, SPI_CLOCK_DIV8);
}

void loop(){
    //Recieve Data From Slave 0, Slave 1
    // MOTOR.setAngle(angle);
}
