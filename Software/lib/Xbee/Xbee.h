#ifndef Xbee_h
#define Xbee_h

#include <Arduino.h>
#include <Config.h>

class Xbees {

public:
    Xbees();
    void init();
    void updateCoordData(int ballX, int ballY, int robotX, int robotY, bool canSeeBall, bool knowsOwnCoords);
    void resetData();
    bool connected();
    void tryConnect();

    int otherBallX, otherBallY, otherX, otherY;
    bool otherCanSeeBall, otherKnowsOwnCoords;
    long timeSinceLastConnected;

private:
    bool robot;
    int _ballX, _ballY, _robotX, _robotY;
    bool _canSeeBall, _knowsOwnCoords;
    void dataSend();
    void dataRead();
    long timeSinceConnected, lastSendTime;
};

#endif
