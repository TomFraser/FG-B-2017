#include <Compass.h>

Compass comp = Compass();

void setup(){
    delay(5000);
    Serial.begin(9600);
    Serial.println("setup");
    Serial.println(comp.calibrate());
    delay(1000);
}

void loop(){
    comp.update();
    Serial.println(comp.getHeading());

}
