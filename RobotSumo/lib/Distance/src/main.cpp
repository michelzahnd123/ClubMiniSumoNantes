#include <Arduino.h>
#include "distance.h"

#define pin_E03AG 35
#define pin_E03RG 36
#define pin_E03RD 34
#define pin_E03AD 39

Distance E03AG(pin_E03AG);
Distance E03RG(pin_E03RG);
Distance E03RD(pin_E03RD);
Distance E03AD(pin_E03AD);

void setup() {
  Serial.begin(115200);
  E03AG.setPinDistance(pin_E03AG);
  E03RG.setPinDistance(pin_E03RG);
  E03RD.setPinDistance(pin_E03RD);
  E03AD.setPinDistance(pin_E03AD);
}

void loop() {
  // Avant Gauche - près=true - loin=false
  if(E03AG.getEtatDistance()==true){
    Serial.println("TOUT PRES : Avant Gauche");
  }
  else{
    Serial.println("Loin : avant gauche");
  }

  // Arrière Gauche - près=true - loin=false
  if(E03RG.getEtatDistance()==true){
    Serial.println("TOUT PRES : ARRière Gauche");
  }
  else{
    Serial.println("Loin : arrière gauche");
  }

    // Arrière Droit - près=true - loin=false
  if(E03RD.getEtatDistance()==true){
    Serial.println("TOUT PRES : ARRière Droit");
  }
  else{
    Serial.println("Loin : arrière droit");
  }

    // Avant Droit - près=true - loin=false
  if(E03AD.getEtatDistance()==true){
    Serial.println("TOUT PRES : Avant Droit");
  }
  else{
    Serial.println("Loin : avant droit");
  }
}