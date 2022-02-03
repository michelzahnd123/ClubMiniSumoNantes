#include <Arduino.h>
#include "tension.h"

#define pin_vlipo 17
Tension vLiPo(pin_vlipo);

void setup() {
  Serial.begin(115200);
  vLiPo.setPinTension(pin_vlipo);
}

void loop() {
  // tension > limite : OK
  if(vLiPo.getEtatTension()==true){
    Serial.println("Alimentation OK");
  }
  else{
    Serial.println("Tension FAIBLE");
  }
  delay(1000);
}
