#include <xbee-arduino.h>
#include <Arduino.h>

class Xbees {
public:
    XBees();
    //Master Commands
    void initMaster();
    bool sendModeChange();

    //Slave Commands
    void initiSlave();
    bool requestModeChange();

    //Shared Commands
    bool isConnected();
    getSelfMode();
    getOtherMode();

private:
    Xbee xbee = Xbee();
    enum mode {
        attack,
        goalie,
        unknown
    }
}
