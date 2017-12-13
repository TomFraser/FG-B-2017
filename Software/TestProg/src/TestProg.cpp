#include <SRF10.h>
#include <Defines.h>

SRF10 fSonar(FRONT_SONAR_ADDR);
SRF10 bSonar(BACK_SONAR_ADDR);
SRF10 lSonar(LEFT_SONAR_ADDR);
SRF10 rSonar(RIGHT_SONAR_ADDR);

void setup(){
  delay(2000);
  Serial.begin(9600);
  Wire.begin();
  Serial.println("setup");
  fSonar.setup();
  bSonar.setup();
  lSonar.setup();
  rSonar.setup();
}

int sonarCount = 0;
long lastRead = 0;
void loop(){

  // int del = 25;
  // fSonar.update();
  // // delay(del);
  // bSonar.update();
  // delay(del);
  // lSonar.update();
  // delay(del);
  // rSonar.update();
  // // delay(del);

  // fSonar.update();
  // bSonar.update();
  // lSonar.update();
  // rSonar.update();
  // delay(100);

  // rSonar.update();

  if((millis() - lastRead) > 50){
    Serial.println(sonarCount%4);
    switch (sonarCount % 4) {
      case 0:
        fSonar.update();
        sonarCount ++;
        lastRead = millis();
        break;
      case 1:
        bSonar.update();
        sonarCount ++;
        lastRead = millis();
        break;
      case 2:
        lSonar.update();
        sonarCount ++;
        lastRead = millis();
        break;
      case 3:
        rSonar.update();
        sonarCount ++;
        lastRead = millis();
        break;
    }
  }

  Serial.print(fSonar.getRange()); Serial.print(" ");
  Serial.print(bSonar.getRange()); Serial.print(" ");
  Serial.print(lSonar.getRange()); Serial.print(" ");
  Serial.print(rSonar.getRange()); Serial.print(" ");
  Serial.println();
}
