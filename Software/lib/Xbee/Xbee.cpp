#include <Xbee.h>

Xbees::Xbees(){

}

void Xbees::init(){
    XBEESERIAL.begin(9600);
    robot = GOALIE;
    resetData();
}

bool Xbees::updateCoordData(int ballX, int ballY, int robotX, int robotY, int canSeeBall, int knowsOwnCoords){
    _ballX = ballX + XBEE_ADDED_CONST;
    _ballY = ballY + XBEE_ADDED_CONST;
    _robotX = robotX + XBEE_ADDED_CONST;
    _robotY = robotY + XBEE_ADDED_CONST;
    _canSeeBall = canSeeBall;
    _knowsOwnCoords = knowsOwnCoords;
    if(millis() > lastSendTime + 20){
      dataSend();
    }
    bool willItConnect = dataRead();
    return willItConnect;
}

void Xbees::resetSendData(){
    _ballX = 65506;
    _ballY = 65506;
    _robotX = 65506;
    _robotY = 65506;
    _canSeeBall = 0;
    _knowsOwnCoords = 0;
}

void Xbees::resetData(){
    otherBallX = 65506;
    otherBallY = 65506;
    otherX = 65506;
    otherY = 65506;
    otherCanSeeBall = 0;
    otherKnowsOwnCoords = 0;
}

bool Xbees::connected(){
    // timeSinceConnected = millis() - timeSinceLastConnected;
    timeSinceConnected = 0;
    if(timeSinceConnected >= 5000){
        return false;
    }else{
        return true;
    }
}

void Xbees::dataSend(){
    XBEESERIAL.write(XBEE_START_BYTE);
    XBEESERIAL.write(XBEE_START_BYTE);
    XBEESERIAL.write(_ballX);
    XBEESERIAL.write(_ballY);
    XBEESERIAL.write(_robotX);
    XBEESERIAL.write(_robotY);
    XBEESERIAL.write(_canSeeBall);
    XBEESERIAL.write(_knowsOwnCoords);
    lastSendTime = millis();
}

bool Xbees::dataRead(){
    while(XBEESERIAL.available() >= XBEE_PACKAGE_SIZE){
        uint8_t firstByte = XBEESERIAL.read();
        uint8_t secondByte = XBEESERIAL.peek();

        if(firstByte == 255 && secondByte == 255){
            timeSinceLastConnected = millis();
            XBEESERIAL.read();

            for(int i = 0; i < XBEE_PACKAGE_SIZE - 4; i++){
                dataBuffer[i] = XBEESERIAL.read() - XBEE_ADDED_CONST;
            }
            dataBuffer[4] = XBEESERIAL.read();
            dataBuffer[5] = XBEESERIAL.read();
            otherBallX = dataBuffer[0];
            otherBallY = dataBuffer[1];
            otherX = dataBuffer[2];
            otherY = dataBuffer[3];
            otherCanSeeBall = dataBuffer[4];
            otherKnowsOwnCoords = dataBuffer[5];
        }
    }
    if((millis() - timeSinceLastConnected) > 2000){
        return false;
    }else{
        return true;
    }
}

void Xbees::tryConnect(){
    if(XBEESERIAL.available()){
        isConnected = true;
    }
}
