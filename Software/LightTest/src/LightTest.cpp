// #include <t3spi.h>
#include <Light.h>

Light Light;

int lightValues[19];// = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
bool results[19];

int threshold = 0;
int counter = 0;

int mode = 3; // 0 = raw vals, 1 = 1's and 0's, 2 = processed angle, 3 = positive only


void setup(){
    Light.init();

    Serial.begin(9600);

    //um what the fuck is this lol
    //LightSPI.begin_SLAVE(ALT_SCK, MOSI, MISO, CS1); //Might be wrong CS pin.
    //LightSPI.setCTAR_SLAVE(16, SPI_MODE0);

    //WOO HOO THIS WORKS
    //Serial.println(Light.getAngle());

}

void loop(){
  if(mode == 0){
    // === Print out raw values ===
    Light.getVals(lightValues);
    for(int i=0; i < 19; i++){
      Serial.print(lightValues[i]);

      if(lightValues[i]<10){
        Serial.print(" ");
      }
      if(lightValues[i]<100){
        Serial.print(" ");
      }
      if(lightValues[i] < 1000){
        Serial.print(" ");
      }
      Serial.print(" ");
    }
    Serial.println();
    delay(100);
  }
  else if(mode == 1){
    // // === Print out on white ===
    Light.readLight();
    Light.getOnWhite(results);
    for(int i=0; i < 19; i++){
      // if(results[1] > 0){
      //   Serial.print(results[i]);
      // }
      // else{
      //   Serial.print(" ");
      // }
      Serial.print(results[i]);
      Serial.print("   ");
    }
    Serial.println();
  }
  else if(mode == 2){
    Light.readLight();
    Serial.println(Light.getAngle());
  }
  else if(mode == 3){
    // // === Print out on white ===
    Light.readLight();
    Light.getOnWhite(results);
    bool print = false;

    for(int i=0; i < 19; i++){
      if(results[i] > 0){
        print = true;
      }
    }

    if(print){
      for(int i=0; i < 19; i++){
        Serial.print(results[i]);
        Serial.print("   ");
      }
      Serial.println();

    }
  }
}
