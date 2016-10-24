#include <CompassController.h>

double CompassController::doubleMod(double value, double maxVal){
    return fmod((value + maxVal), maxVal);
}

double CompassController::calcHeading(double heading){
    if(heading > 180){
        heading = 360 - heading;
        return -heading;
    }
    else{
        return heading;
    }
}

Vector3D CompassController::calcGyro(){
    uint8_t buffer[14];
    I2Cread(COMPASS_ADDRESS, 0x3B, 14, buffer);
    int16_t gx = -(buffer[8] << 8 | buffer[1]);
    int16_t gy = -(buffer[10] << 8 | buffer[11]);
    int16_t gz = buffer[12] << 8 | buffer[13];
    Vector3D returnVector = {convertRawGyro(gx), convertRawGyro(gy), convertRawGyro(gz)};
    return returnVector;
}

void CompassController::I2Cread(uint8_t Address, uint8_t Register, uint8_t Nbytes, uint8_t* Data)
{

  // Set register address
  Wire.beginTransmission(Address);
  Wire.write(Register);
  Wire.endTransmission();

  // Read Nbytes
  Wire.requestFrom(Address, Nbytes);
  uint8_t index=0;
  while (Wire.available())
    Data[index++]=Wire.read();
}

// Write a byte (Data) in device (Address) at register (Register)
void CompassController::I2CwriteByte(uint8_t Address, uint8_t Register, uint8_t Data)
{
  // Set register address
  Wire.beginTransmission(Address);
  Wire.write(Register);
  Wire.write(Data);
  Wire.endTransmission();
}
