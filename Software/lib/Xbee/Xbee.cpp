#include <Xbee.h>

Xbees::Xbees(){

}

void Xbees::init(){
    XBEESERIAL.begin(9600);
    robot = GOALIE;
    resetData();
}

void Xbees::updateCoordData(int ballX, int ballY, int robotX, int robotY){
    _ballX = ballX + XBEE_ADDED_CONST;
    _ballY = ballY + XBEE_ADDED_CONST;
    _robotX = robotX + XBEE_ADDED_CONST;
    _robotY = robotY + XBEE_ADDED_CONST;
    dataSend();
}

void Xbees::resetData(){
    _ballX = 65506;
    _ballY = 65506;
    _robotX = 65506;
    _robotY = 65506;
}

bool Xbees::connected(){
    timeSinceConnected = millis() - timeSinceLastConnected;
    if(!XBEESERIAL.available() && timeSinceConnected >= 2000){
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
}

void Xbees::dataRead(){
    while(XBEESERIAL.available() >= XBEE_PACKAGE_SIZE){
        uint8_t firstByte = XBEESERIAL.read();
        uint8_t secondByte = XBEESERIAL.peek();

        if(firstByte == 255 && secondByte == 255){
            XBEESERIAL.read();

            int dataBuffer[XBEE_PACKAGE_SIZE - 2];
            for(int i = 0; i < XBEE_PACKAGE_SIZE - 2; i++){
                dataBuffer[i] = XBEESERIAL.read() - XBEE_ADDED_CONST;
            }
            otherBallX = dataBuffer[0];
            otherBallY = dataBuffer[0];
            otherX = dataBuffer[0];
            otherY = dataBuffer[0];
        }
    }
}
