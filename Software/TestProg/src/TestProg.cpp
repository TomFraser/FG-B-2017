#include <SRF10.h>
#include <Defines.h>

SRF10 fSonar(FRONT_SONAR_ADDR, byte(0x0C), byte(0x0D));
SRF10 bSonar(BACK_SONAR_ADDR, byte(0x0C), byte(0x0D));

void setup(){
  Serial.println("sss");
  delay(3000);
  Serial.begin(9600);
  Wire.begin();
  Serial.println("setup");
  fSonar.setup();
  bSonar.setup();
  Serial.println("asldfkj");
}

int sonarCount = 0;
long lastRead = 0;
void loop(){
  Serial.println("a");
  if((millis() - lastRead) > 50){
    Serial.println(sonarCount%2);
    switch (sonarCount % 2) {
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
    }
  }

  Serial.print(fSonar.getRange()); Serial.print(" ");
  Serial.print(bSonar.getRange()); Serial.print(" ");
  Serial.println();
}
