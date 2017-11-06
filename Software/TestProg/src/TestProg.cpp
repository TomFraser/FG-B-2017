#include <DirectionController.h>

DirectionController directionController = DirectionController();

void setup(){
    Serial.begin(9600);
}

void loop(){
  directionController.updateGameData(65506, 90, 0);
  // directionController.updateGoalData(0, -30, 0, -30);
  directionController.updateGoalData(114, 280.3, 0, -30);
  directionController.calulate();

  // atan2(dx, dy)
  // Serial.println(atan2(-5, -80)*radToAng);

  Serial.print("Dir: "); Serial.print(directionController.getDirection()); Serial.print(" Speed: "); Serial.println(directionController.getSpeed());


}
