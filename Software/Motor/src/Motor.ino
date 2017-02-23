#include <Config.h>
#include <DirectionController.h>
#include <t3spi.h>
#include <Kicker.h>
#include <Buzzer.h>
#include <fgbcommon.h>

// MotorController MOTOR = MotorController();
// T3SPI MASTER_TEENSY;
// Kicker kicker = Kicker();
DirectionController direction = DirectionController();
// Buzzer buzzer = Buzzer();

double tsopAng = 0.00;

int counter = 0;

void setup(){
    // MASTER_TEENSY.begin_MASTER(ALT_SCK, MOSI, MISO, CS1, CS_ActiveLOW);
    // MASTER_TEENSY.setCTAR(CTAR_0, 16, SPI_MODE0, LSB_FIRST, SPI_CLOCK_DIV8);
    // buzzer.readyTone();
}

void loop(){ //Things to do before running the program, setting up the pins!!!!!
    //Recieve Data From Slave 0, Slave 1

    direction.setPWM(255);

    // kicker.kickerReady(); //Kicker
    // kicker.checkLightGate();
    // kicker.kickBall();
}

void testDirection(){
    direction.setPWM(255);
    delay(2000);
    direction.setPWM(-255);
    delay(2000);
}

void incrementSpeed(){
    direction.setPWM(counter);
    delay(100);
    counter++;
    if(counter >= 255){
        counter = 0;
    }
}
