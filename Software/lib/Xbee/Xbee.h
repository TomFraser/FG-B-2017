#ifndef Xbee_h
#define Xbee_h

#include <Arduino.h>
#include <Config.h>

class Xbees {

public:
    Xbees();
    void init();
    bool updateCoordData(int ballX, int ballY, int robotX, int robotY, int canSeeBall, int knowsOwnCoords);
    void resetData();
    void resetSendData();
    bool connected();
    void tryConnect();

    int otherBallX, otherBallY, otherX, otherY;
    int otherCanSeeBall, otherKnowsOwnCoords;
    long timeSinceLastConnected;

private:
    bool robot, isConnected, connectedThisLoop;
    int _ballX, _ballY, _robotX, _robotY;
    bool _canSeeBall, _knowsOwnCoords;
    void dataSend();
    bool dataRead();
    long timeSinceConnected, lastSendTime;
};

#endif
