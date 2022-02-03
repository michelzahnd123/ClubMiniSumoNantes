#include <Arduino.h>
#include "accelero.h"

#define pin_m6050 16
Accelero M6050(pin_m6050);

void setup() {
  Serial.begin(115200);
  M6050.setPinAccelero(pin_m6050);
}

void loop() {
  // INT
  if(M6050.getEtatAccelero()==true){
    Serial.println("Accéléro actif");
  }
  else{
    Serial.println("Accéléro ENDORMI");
  }
  delay(1000);
}
