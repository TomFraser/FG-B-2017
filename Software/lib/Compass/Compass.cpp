#include <Compass.h>

//========Constructor========
Compass::Compass(){

}

void Compass::init(){

    I2CwriteByte(IMU_ADDRESS, 29, 0x06);
    I2CwriteByte(IMU_ADDRESS, 26, 0x06);
    I2CwriteByte(IMU_ADDRESS, 27, GYRO_FULL_SCALE_500_DPS);
    I2CwriteByte(IMU_ADDRESS, 28, ACC_FULL_SCALE_2_G);
    I2CwriteByte(IMU_ADDRESS, 0x37, 0x02);
    I2CwriteByte(MAG_ADDRESS, 0x0A, 0x16);

    setTarget(0);
}

//========Init Calibrate========
double Compass::calibrate(){
    read();
    Serial.println("Read Done");

    delay(COMPASS_CALIBRATION_TIME);
    Serial.println("Delay time done");
    double reading = 0;
    for(int i=0; i<COMPASS_CALIBRATION_NUMBER; i++){
        reading += (double) read().z;
    }
    calibration = reading/COMPASS_CALIBRATION_NUMBER;

    return calibration;
}

//=====Read / Update======
Vector3D Compass::read(){
    uint8_t buffer[14];
    I2Cread(IMU_ADDRESS, 0x3B, 14, buffer);
    int16_t gx = -(buffer[8] << 8 | buffer[1]);
    int16_t gy = -(buffer[10] << 8 | buffer[11]);
    int16_t gz = buffer[12] << 8 | buffer[13];
    Vector3D returnVector = {convertRawGyro(gx), convertRawGyro(gy), convertRawGyro(gz)};
    return returnVector;
}

void Compass::update() {
    double reading = (double) read().z;

	long currentTime = micros();
    heading += (((double)(currentTime - previousTime) / 1000000.0) * (reading - calibration));
	heading = doubleMod(heading, 360.0);
	previousTime = currentTime;
}

//=======Set Target=======
void Compass::setTarget(double target_){
    target = -target_;
}

//=======Get Heading======
double Compass::getHeading(){
    double curr = heading > 180 ? -(360-heading + target) : heading - target;// + target; //Fix this
    return curr;
}


//======Utility Functions======
double Compass::doubleMod(double value, double maxVal){
    return fmod((value + maxVal), maxVal);
}

void Compass::I2Cread(uint8_t Address, uint8_t Register, uint8_t Nbytes, uint8_t* Data)
{

  // Set register address
  Wire1.beginTransmission(Address);
  Wire1.write(Register);
  Wire1.endTransmission();

  // Read Nbytes
  Wire1.requestFrom(Address, Nbytes);
  uint8_t index=0;
  while (Wire1.available())
    Data[index++]=Wire1.read();
}

// Write a byte (Data) in device (Address) at register (Register)
void Compass::I2CwriteByte(uint8_t Address, uint8_t Register, uint8_t Data)
{
  // Set register address
  Wire1.beginTransmission(Address);
  Wire1.write(Register);
  Wire1.write(Data);
  Wire1.endTransmission();
}
