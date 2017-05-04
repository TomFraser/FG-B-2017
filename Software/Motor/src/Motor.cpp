#include <Config.h>
#include <DirectionController.h>
#include <Kicker.h>
#include <Buzzer.h>
#include <fgbcommon.h>
#include <PixyI2C.h>
#include <Motor.h>
#include <Pins.h>
#include <Defender.h>
#include <SPI.h>

double angle = 0;
double lightAngle = 0;

DirectionController direction = DirectionController();

int requestTSOP(int toSend){
    digitalWrite(TSOP_SS, LOW);
    int response = SPI.transfer16(toSend);
    digitalWrite(TSOP_SS, HIGH);
    #if SPI_DEBUG
    Serial.println(response);
    #endif
}

int requestLight(int toSend){
    digitalWrite(LIGHT_SS, LOW);
    int response = SPI.transfer16(toSend);
    digitalWrite(LIGHT_SS, HIGH);
    #if SPI_DEBUG
    Serial.println(response);
    #endif
}

void setup(){
    //I2C SETUP
    Wire1.begin(I2C_MASTER, 0x00, I2C_PINS_29_30, I2C_PULLUP_EXT, 400000);
    Wire1.setDefaultTimeout(200000); // 200ms

    //SPI SETUP
    pinMode(TSOP_SS, OUTPUT);
    pinMode(LIGHT_SS, OUTPUT);
    SPI.begin();
    digitalWrite(TSOP_SS, HIGH);
    digitalWrite(LIGHT_SS, HIGH);
    SPI.setSCK(ALT_SCK);
    SPI.setClockDivider(SPI_CLOCK_DIV8);

    direction.init();
}

void loop(){
    //Send and recieve data
    int angle = requestTSOP(TSOP_REQ_BALL);
    delay(1000);
    int lightAngle = requestLight(LIGHT_REQ_LINE);

    direction.calcMotors(180.00, lightAngle, 0.00);
}
