#include <Config.h>
#include <DirectionController.h>
#include <Kicker.h>
#include <Buzzer.h>
#include <fgbcommon.h>
#include <PixyI2C.h>
#include <Motor.h>
#include <Pins.h>
#include <Defender.h>
#include <Debug.h>

debugClass debug = debugClass();

#include <SPI.h>

// Motor motorD = Motor(MOTOR_A_PWM, MOTOR_A_DIR, MOTOR_A_BRK, MOTOR_A_REV); //Really Motor D
// Motor motorC = Motor(MOTOR_B_PWM, MOTOR_B_DIR, MOTOR_B_BRK, MOTOR_B_REV); //Really Motor A
// Motor motorB = Motor(MOTOR_C_PWM, MOTOR_C_DIR, MOTOR_C_BRK, MOTOR_C_REV);
// Motor motorA = Motor(MOTOR_D_PWM, MOTOR_D_DIR, MOTOR_D_BRK, MOTOR_D_REV);

//C, A, B, D

volatile uint16_t dataOut[DATA_LENGTH] = {};
volatile uint16_t dataIn[DATA_LENGTH] = {};

long initialTime = 0;
long currentTime = 0;
double angle;
double lightAngle = 0;

Defender defender = Defender();
Kicker kicker = Kicker();
DirectionController direction = DirectionController();
// Buzzer buzzer = Buzzer();

int currentAngle = 0;

#define TSOP_SS 16
#define LIGHT_SS 15
#define ALT_SCK 14

void setup(){
    Wire1.begin(I2C_MASTER, 0x00, I2C_PINS_29_30, I2C_PULLUP_EXT, 400000);
    Wire1.setDefaultTimeout(200000); // 200ms

    direction.init();

    pinMode(KICKER_PIN, OUTPUT);

    //SPI SETUP
    pinMode(LIGHT_SS, OUTPUT);
    pinMode(TSOP_SS, OUTPUT);
    SPI.begin();
    digitalWrite(TSOP_SS, HIGH);
    digitalWrite(LIGHT_SS, HIGH);
    SPI.setSCK(ALT_SCK);
    // pinMode(12, INPUT);
    SPI.setClockDivider(SPI_CLOCK_DIV8);
    defender.init();

}

void loop(){
    //Send and recieve data
    digitalWrite(TSOP_SS, LOW); //Set cs low
    delay(1);
    SPI.transfer16(512); //Transfer 512 and recieve value
    int response = SPI.transfer16(512); //Transfer 512 and recieve value
    digitalWrite(TSOP_SS, HIGH); //Set cs high
    // Serial.println(response);

    delay(20);

    digitalWrite(LIGHT_SS, LOW);
    delay(1);
    SPI.transfer16(512);
    int lightResponse = SPI.transfer16(512);
    digitalWrite(LIGHT_SS, HIGH);

    // direction.calcMotors(response, 0.00, 0.00);

    // Vector3D defenderGo = defender.calcDirection(response); //This method returns a 2dvector where the direction is the direction and the strength is the rotation. I didnt want to make another struct.
    Vector3D defenderGo = defender.determineDefense(response);
    direction.calcMotors(defenderGo.x, 0.00, defenderGo.z, defenderGo.y, response);


    // if(random(0, 200) == 5){
    //     kicker.kickBall();
    // }

}
