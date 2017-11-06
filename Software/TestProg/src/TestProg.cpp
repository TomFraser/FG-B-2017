#include <DirectionController.h>

DirectionController directionController = DirectionController();

void setup(){
    Serial.begin(9600);
}

void loop(){
  directionController.updateGameData(65506, 65506, 0);
  directionController.updateGoalData(114, 280.3, 0, -30);
  directionController.calulate();

}
