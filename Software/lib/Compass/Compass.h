#ifndef Compass_h
#define Compass_h

#include <Config.h>
#include <Pins.h>
#include <Defines.h>

#include <Wire.h>
#include <Vector3D.h>
#include <math.h>

//The Compass Class
class Compass {

public:
    Compass();

    //Calibrates the compass to account for gyro drift
    double calibrate();

    //Read the gyro on MPU9250
    Vector3D read();

    //Gets a heading from the reading of the gyro
    void update();

    //Gets the heading in a simple way
    double getHeading();

    //Modify the target heading of the compass so that we can angle inward
    void setTarget(double target_);

private:
    long previousTime;
    double calibration;
    double heading;
    double target;

    //A simple double mod function
    double doubleMod(double value, double maxVal);

    //Simple I2C read
    void I2Cread(uint8_t Address, uint8_t Register, uint8_t Nbytes, uint8_t* Data);

    //Simpe I2C write
    void I2CwriteByte(uint8_t Address, uint8_t Register, uint8_t Data);

    // Since we are using 500 degrees/seconds range
    // -500 maps to a raw value of -32768
    // +500 maps to a raw value of 32767
    double convertRawGyro(int16_t raw) {

        return (raw * 500.0) / 32768.0;
    }

};

#endif
