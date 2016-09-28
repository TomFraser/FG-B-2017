#ifndef I2CController_h
#define I2CController_h

#include <Config.h>

class I2CController{
public:
    I2CController();
    void beginMaster();
    void beginMaster(/*INSERT CRAP HERE*/int blah);
    void beginSlave();
    void beginSlave(/*INSERT CRAP HERE*/int blah);

private:
    void I2CSend();
    void I2CRecieve();

};

#endif
