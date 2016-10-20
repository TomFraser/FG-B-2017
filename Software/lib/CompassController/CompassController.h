#ifndef CompassController_h
#define CompassController_h

// #include <Config.h>
#include <Wire.h>
#include <Math.h>


class CompassController{

public:
    CompassController(){};
    double doubleMod(double value, double maxVal);
    double calcHeading(double heading);

    Vector3D calcGyro();

private:
    Madgwick filter;
    void I2Cread(uint8_t Address, uint8_t Register, uint8_t Nbytes, uint8_t* Data);
    void I2CwriteByte(uint8_t Address, uint8_t Register, uint8_t Data);

};

struct Vector3D {
    int x;
    int y;
    int z;
};

#endif
