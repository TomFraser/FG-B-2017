#ifndef Srf10_h
#define Srf10_h

#include <Arduino.h>
#include <i2c_t3.h>

class Srf10{
public:
    Srf10(){};
    void init();
    void read();
private:

};

class Srf10Array{
public:
    void init();
    void readSensors();
private:
    void sort();

};

#endif
