#include "Slave.h"

void Slave::init(int csPin) {
    cs = csPin;

    spi.enableCS(cs, CS_ActiveLOW);
}

uint16_t Slave::transaction(uint16_t command) {
    dataOut[0] = (uint16_t)command;

    for (int i = 0; i < 3; i++) {
        spi.txrx16(dataOut, dataIn, 1, CTAR_0, cs);
    }

    return dataIn[0];
}

void SlaveLightSensor::init() {
    Slave::init(LIGHT_SS);
}

void SlaveTSOP::init() {
    Slave::init(TSOP_SS);
}
