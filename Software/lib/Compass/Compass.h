#ifndef Compass_h
#define Compass_h

#include <Config.h>
#include <Pins.h>
#include <Defines.h>

#include <i2c_t3.h>
#include <Vector3D.h>
#include <math.h>


class Compass {

public:
    Compass();
    void init();
    double calibrate();
    Vector3D read();
    void update();
    double getHeading();
    void setTarget(double target_);

private:
    long previousTime;
    double calibration;
    double heading;
    double target;

    double doubleMod(double value, double maxVal);

    void I2Cread(uint8_t Address, uint8_t Register, uint8_t Nbytes, uint8_t* Data);
    void I2CwriteByte(uint8_t Address, uint8_t Register, uint8_t Data);

    double convertRawGyro(int16_t raw) {
        return (raw * 500.0) / 32768.0;
    }

};

#endif
