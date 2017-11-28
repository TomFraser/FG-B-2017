#ifndef Xbee_h
#define Xbee_h

#include <Arduino.h>
#include <Config.h>

class Xbees {

public:
    Xbees();
    void init();
    void updateCoordData(int ballX, int ballY, int robotX, int robotY);
    void resetData();
    bool connected();

    int otherBallX, otherBallY, otherX, otherY;

private:
    bool robot;
    int _ballX, _ballY, _robotX, _robotY;
    void dataSend();
    void dataRead();
    long timeSinceConnected;
    long timeSinceConnected;
};

#endif
