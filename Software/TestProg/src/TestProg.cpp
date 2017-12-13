#include <SRF10.h>

SRF10 sonar(112);

void setup(){
  delay(2000);
  Serial.begin(9600);
  Serial.println("setup");
}

void loop(){
  sonar.update();
  Serial.println(sonar.getRange());
}
