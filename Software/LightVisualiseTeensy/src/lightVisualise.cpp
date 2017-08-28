// #include <t3spi.h>
#include <Light.h>

Light Light;

int lightValues[19];// = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
bool results[19];

int threshold = 0;
int counter = 0;




void setup(){
  Light.init();
  Serial.begin(9600);

  // wait for connection
  while(true){
    if(Serial.available()){
      if(Serial.read()){
        // turn on led cause i can
        pinMode(13, OUTPUT);
        digitalWrite(13, HIGH);
        break;
     }
   }
 }

}

void loop(){
  // // === Print out on white ===
  Light.readLight();
  Light.getOnWhite(results);
  for(int i=0; i < 19; i++){
    Serial.print(results[i]); Serial.print(" ");
  }
  Serial.println();

  Serial.println(Light.getAngle());
}
