#ifndef SLAVE_H
#define SLAVE_H

#include <t3spi.h>
#include <Pins.h>
#include <Config.h>

class Slave {
public:
    void init(int csPin);
    uint16_t transaction(uint16_t command);
    T3SPI spi;

private:
    volatile uint16_t dataIn[1];
    volatile uint16_t dataOut[1];
    int cs;
};

class SlaveLightSensor: public Slave {
public:
    void init();

};

class SlaveTSOP: public Slave {
public:
    void init();
};

#endif // SLAVE_H
