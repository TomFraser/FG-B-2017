#ifndef ReadTSOPS_h
#define ReadTSOPS_h

#include </Users/Thomas/Documents/Developer/FG\&B/Software/Config/Config.h>

class ReadTSOPS{

private:
    int sensors[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
    int values[12];
    int index;

public:
    ReadTSOPS();
    void read(int mode);
    void reset();
    void stop();

    int bestSensor;
};

#endif
