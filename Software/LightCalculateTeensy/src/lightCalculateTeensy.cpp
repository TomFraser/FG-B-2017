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
  if(Serial.available()){
    
    Light.setOnWhite(data);
    Serial.println(Light.getAngle());
  }
}
