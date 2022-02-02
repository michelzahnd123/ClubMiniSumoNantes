#include <Arduino.h>
#include "noirblanc.h"

#define pin_cny70AV 18
#define pin_cny70D 19
#define pin_cny70G 4

NoirBlanc cny70AV(pin_cny70AV);
NoirBlanc cny70D(pin_cny70D);
NoirBlanc cny70G(pin_cny70G);

void setup() {
  Serial.begin(115200);
  cny70AV.setPinNoirBlanc(pin_cny70AV);
  cny70D.setPinNoirBlanc(pin_cny70D);
  cny70G.setPinNoirBlanc(pin_cny70G);
}

void loop() {
  // AVANT : dojo=noir - ligne=blanc
  if(cny70AV.getEtatNoirBlanc()==true){
    Serial.println("Avant sur le dojo");
  }
  else{
    Serial.println("AVANT sur le BLANC");
  }

  // Côté DROIT : dojo=noir - ligne=blanc
  if(cny70D.getEtatNoirBlanc()==true){
    Serial.println("Côté droit sur le dojo");
  }
  else{
    Serial.println("COTE DROIT sur le BLANC");
  }
  
  // Côté GAUCHE : dojo=noir - ligne=blanc
  if(cny70G.getEtatNoirBlanc()==true){
    Serial.println("Côté gauche sur le dojo");
  }
  else{
    Serial.println("COTE GAUCHE sur le BLANC");
  }
  delay(1000);
}