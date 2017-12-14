#ifndef SRF10_h
#define SRF10_h

#include <Config.h>
#include <Common.h>
#include <Pins.h>
#include <Defines.h>
#include <Arduino.h>
#include <i2c_t3.h>

#define CMD (byte)0x00 // Command byte, values of 0 being sent with write have to be masked as a byte to stop them being misinterpreted as NULL this is a bug with arduino 1.0
#define RANGEBYTE 0x02 // Byte for start of ranging data
#define WAIT_TIME 65

class SRF10{

public:
  SRF10(uint8_t address_, byte gain_, byte range_);
  void setup();
  bool update();
  int getRange();

private:
  uint8_t address;
  int range = 0;
  long lastRead = 0;
  bool ranging = false;
  void startRanging();
  int read(byte register_ = RANGEBYTE);
  void writeRegister(byte register_, byte data);
  byte gain;
  byte setRange;


};
#endif
