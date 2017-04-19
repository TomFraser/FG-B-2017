#include <Config.h>
#include <DirectionController.h>
#include <t3spi.h>
#include <Kicker.h>
#include <Buzzer.h>
#include <fgbcommon.h>
#include <PixyI2C.h>
#include <Motor.h>
#include <Pins.h>

Motor motorD = Motor(MOTOR_A_PWM, MOTOR_A_DIR, MOTOR_A_BRK, MOTOR_A_REV); //Really Motor D
Motor motorC = Motor(MOTOR_B_PWM, MOTOR_B_DIR, MOTOR_B_BRK, MOTOR_B_REV); //Really Motor A
Motor motorB = Motor(MOTOR_C_PWM, MOTOR_C_DIR, MOTOR_C_BRK, MOTOR_C_REV);
Motor motorA = Motor(MOTOR_D_PWM, MOTOR_D_DIR, MOTOR_D_BRK, MOTOR_D_REV);

//C, A, B, D

volatile uint16_t dataOut[DATA_LENGTH] = {};
volatile uint16_t dataIn[DATA_LENGTH] = {};

// MotorController MOTOR = MotorController();
T3SPI MASTER_TEENSY;
// Kicker kicker = Kicker();
DirectionController direction = DirectionController();
// Buzzer buzzer = Buzzer();

double tsopAng = 0.00;

int counter = 0;

void setup(){
    initComs();
    initTsopComs();
    // initLightComs();

    pinMode(A12, INPUT);
    direction.init();
}

void loop(){
    //Motor Transmission
    callTsops(true);
    //callLight(true);
    delay(50);


    direction.calcMotors(angle, 0.00, 0.00);
}

void blinkLED(){
    digitalWrite(13, HIGH);
    delay(1000);
    digitalWrite(13, LOW);
    delay(1000);
}

void initComs(){
    Wire1.begin(I2C_MASTER, 0x00, I2C_PINS_29_30, I2C_PULLUP_EXT, 400000);
    Wire1.setDefaultTimeout(200000); // 200ms

    MASTER_TEENSY.begin_MASTER(ALT_SCK, MOSI, MISO, CS0, CS_ActiveHIGH); //Begin Master
    MASTER_TEENSY.setCTAR(CTAR_0, 16, SPI_MODE0, LSB_FIRST, SPI_CLOCK_DIV8); //Set Packet Cache
}

void initTsopComs(){
    MASTER_TEENSY.enableCS(CS4, CS_ActiveHIGH); //Set CS for TSOPs
}

void initLightComs(){
    MASTER_TEENSY.enableCS(CS0, CS_ActiveHIGH); //Set CS for LIGHTs
}

void callTsops(bool type){
    if(type){
        MASTER_TEENSY.txrx16(dataOut, dataIn, DATA_LENGTH, CTAR_0, CS4); //Pull data from TSOPs
        double angle = dataIn[0];
        #if DEBUG
        serial.print("TSOP: ");
        serial.println(angle);
        #endif
    }
}

void callLight(bool type){
    if(type){
        MASTER_TEENSY.txrx16(dataOut, dataIn, DATA_LENGTH, CTAR_0, CS4); //Pull data from LIGHTs
        double lightAngle = dataIn[0];
        #if DEBUG
        Serial.print("LIGHT: ");
        Serial.println(lightAngle);
        #endif
    }
}
