#ifndef ReadTSOPS_h
#define ReadTSOPS_h

#include <Config.h>

class ReadTSOPS{

private:
    int sensors[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
    int values[12];
    int index;
    bool angleToBall;
    bool angleOrbit;

public:
    ReadTSOPS();
    void readMode(int mode);
    void read();
    void reset();
    void stop();
    bool moveTangent();

    int bestSensor;
};

#endif
