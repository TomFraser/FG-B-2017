// #include <t3spi.h>
#include <Light.h>

Light Light;

int lightValues[19];// = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
bool results[19];

int threshold = 0;

void setup(){
    Light.init();

    Serial.begin(9600);
    delay(3000);
    Serial.println("end setup");

    //um what the fuck is this lol
    //LightSPI.begin_SLAVE(ALT_SCK, MOSI, MISO, CS1); //Might be wrong CS pin.
    //LightSPI.setCTAR_SLAVE(16, SPI_MODE0);

    //WOO HOO THIS WORKS
    //Serial.println(Light.getAngle());

}

void loop(){
    // // === Print out raw values ===
    // Light.getVals(lightValues);
    // for(int i=0; i < 19; i++){
    //   // if(i==3){
    //   //   Serial.print("fuk");
    //   // }
    //   // else{
    //   //   Serial.print(lightValues[i]);
    //   // }
    //   Serial.print(lightValues[i]);
    //
    //   if(lightValues[i]<10){
    //     Serial.print(" ");
    //   }
    //   if(lightValues[i]<100){
    //     Serial.print(" ");
    //   }
    //   Serial.print(" ");
    // }
    // Serial.println();

    // // === Print out on white ===
    // Light.readLight();
    // Light.getOnWhite(results);
    // for(int i=0; i < 19; i++){
    //   // if(results[1] > 0){
    //   //   Serial.print(results[i]);
    //   // }
    //   // else{
    //   //   Serial.print(" ");
    //   // }
    //   Serial.print(results[i]);
    //   Serial.print("   ");
    // }
    // Serial.println();

    double lightAngle = Light.getAngle();
    if(lightAngle > -1){
      Serial.println(lightAngle);
    }

    delay(100);
}
