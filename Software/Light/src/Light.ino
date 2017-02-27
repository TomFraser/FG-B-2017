//#include <t3spi.h>
//#include <Light.h>

//T3SPI LightSPI;
//Light Light;

//int lightValues[19] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

void setup(){
    Serial.begin(9600);
    pinMode(A7, INPUT);
    //um what the fuck is this lol
    //LightSPI.begin_SLAVE(ALT_SCK, MOSI, MISO, CS1); //Might be wrong CS pin.
    //LightSPI.setCTAR_SLAVE(16, SPI_MODE0);

    //Serial.print(Light.getAngle());
}

void loop(){
    //Light.getVals(lightValues);
    //for(int i=0; i < 19; i++){
      //Serial.print(lightValues[i]);
      //Serial.print(" ");
    //}
    //Serial.println();
    Serial.println(analogRead(A7));
    delay(100);
}
