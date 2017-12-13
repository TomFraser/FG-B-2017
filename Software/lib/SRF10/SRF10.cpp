#include <SRF10.h>

SRF10::SRF10(uint8_t address_){
    //setup
    address = address_;
}

void SRF10::setup(){
  // do stuff just not yet
  // set gain
  // set something else
}

void SRF10::update(){
  if(!ranging){
    // not ranging -> start ranging, not gonna be ready to read yet
    startRanging();
    ranging = true;
  }
  else{
    // already ranging -> check if ready to read
    if(millis()-lastRead > WAIT_TIME){
      range = read();
      ranging = false;
      lastRead = millis();
    }
  }
}

void SRF10::startRanging(){
  // Tell it to range
  Wire.beginTransmission(address);
  Wire.write(CMD);
  Wire.write(0x51); //0x51 = start ranging
  Wire.endTransmission();
}

int SRF10::read(byte register_){
  // ask for data
  Wire.beginTransmission(address);
  Wire.write(register_); //register for range
  Wire.endTransmission();

  // get the data
  Wire.requestFrom(address, 2);
  if(Wire.available() == 0){
    return -1;
  }

  while(Wire.available() < 2);

  // return the data
  return (Wire.read() << 8) + Wire.read();

}

int SRF10::getRange(){
  return range;
}
