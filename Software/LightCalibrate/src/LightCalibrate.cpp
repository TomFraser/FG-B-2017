// #include <t3spi.h>
#include <Light.h>

Light Light;

int lightValues[19];

int numGreenCycles = 10000;
int numWhiteCycles = 20000;


// int offset = -40;
double percentage = 0.2;

// MADE A CHANGE TO THE ALGORITHM - MAKE SURE IT WORKS

int greenMax[19] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int whiteMax[19] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};


void setup(){
    Light.init();
    Serial.begin(9600);
    delay(2000);

}

void loop(){

    // ================ Green ======================

    Serial.println("Place robot on green");
    Serial.print("5 ");delay(1000); Serial.print("4 ");delay(1000);Serial.print("3 ");delay(1000); Serial.print("2 ");delay(1000);Serial.println("1 ");


    for(int i=0; i<numGreenCycles; i++){
      Light.getVals(lightValues);
      for(int j=0; j<19; j++){
        if(lightValues[j] > greenMax[j]){
          greenMax[j] = lightValues[j];
        }
      }
      delay(1);
      Serial.println(numGreenCycles-i);
    }

    // ===================== White =====================

    Serial.println("Move Robot over white in, ");
    Serial.print("5 ");delay(1000); Serial.print("4 ");delay(1000);Serial.print("3 ");delay(1000); Serial.print("2 ");delay(1000);Serial.println("1 ");


    for(int i=0; i<numWhiteCycles; i++){
      Light.getVals(lightValues);
      for(int j=0; j<19; j++){
        if(lightValues[j] > whiteMax[j]){
          whiteMax[j] = lightValues[j];
        }
      }
      delay(1);
      Serial.println(numWhiteCycles-i);
    }

    // ===================== Prints =======================

    Serial.println("Green Max:");

    for(int k=0; k < 19; k++){
      Serial.print(greenMax[k]);
      if(greenMax[k]<10){
        Serial.print(" ");
      }
      if(greenMax[k]<100){
        Serial.print(" ");
      }
      if(greenMax[k]<1000){
        Serial.print(" ");
      }
      Serial.print(" ");
    }
    Serial.println();

    Serial.println("White Max:");

    for(int k=0; k < 19; k++){
      Serial.print(whiteMax[k]);
      if(whiteMax[k]<10){
        Serial.print(" ");
      }
      if(whiteMax[k]<100){
        Serial.print(" ");
      }
      if(whiteMax[k]<1000){
        Serial.print(" ");
      }
      Serial.print(" ");
    }
    Serial.println();

    // ===================== Difference White - Green ==================
    int diff[19];
    for(int i=0; i<19; i++)
    {
      diff[i] = whiteMax[i] - greenMax[i];
    }

    Serial.println("Diff:");

    for(int k=0; k < 19; k++){
      Serial.print(diff[k]);
      if(diff[k]<10){
        Serial.print(" ");
      }
      if(diff[k]<100){
        Serial.print(" ");
      }
      if(diff[k]<1000){
        Serial.print(" ");
      }
      Serial.print(" ");
    }
    Serial.println();


    // ======================== Usable Calibration =====================
    int calb[19];
    for(int i=0; i<19; i++)
    {
      // calb[i] = greenMax[i] + (int)(diff[i]/2) + offset;
      calb[i] = greenMax[i] + (int)((diff[i]/2)*percentage);
    }

    #if !ROBOT
      calb[17] = -1;
    #endif

    Serial.println("Final:");

    for(int k=0; k < 19; k++){
      Serial.print(calb[k]);
      if(calb[k]<10){
        Serial.print(" ");
      }
      if(calb[k]<100){
        Serial.print(" ");
      }
      if(calb[k]<1000){
        Serial.print(" ");
      }
      Serial.print(" ");
    }
    Serial.println();

    Serial.println("Usable:");
    Serial.print("{");
    for(int k=0; k < 18; k++){
      Serial.print(calb[k]);Serial.print(", ");
    }
    Serial.print(calb[18]); Serial.println("};");


    delay(2000);


}
