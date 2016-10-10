#ifndef Compass_h
#define Compass_h

#include <Config.h>
#include <Wire.h>
#include <Vector3D.h>
#include <Math.h>


class Compass{

public:
    Compass();
    double calibrate();
    Vector3D read();
    void update();
    double getHeading();

private:
    double heading;
    long previousTime;
    double calibration;

    double doubleMod(double value, double maxVal);

    void I2Cread(uint8_t Address, uint8_t Register, uint8_t Nbytes, uint8_t* Data);
    void I2CwriteByte(uint8_t Address, uint8_t Register, uint8_t Data);

    double convertRawGyro(int16_t raw) {
        // Since we are using 500 degrees/seconds range
        // -500 maps to a raw value of -32768
        // +500 maps to a raw value of 32767

        double g = (raw * 500.0) / 32768.0;
        return g;
    }

};

#endif
