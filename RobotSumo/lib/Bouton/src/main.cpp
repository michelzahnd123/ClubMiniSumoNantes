#include <Arduino.h>
#include "bouton.h"
#define pin_boutonON 15
#define pin_contactAV 5

Bouton boutonON(pin_boutonON);
Bouton contactAV(pin_contactAV);

void setup() {
  Serial.begin(115200);
  boutonON.setPinBouton(pin_boutonON);
  contactAV.setPinBouton(pin_contactAV);
}

void loop() {
  // ----- appui sur "bouton On"
  if(boutonON.getEtatBouton()==true){
    Serial.println("le ROBOT est démarré");
  }
  else{
    Serial.println("rien");
  }
  // ----- appui sur "contact Avant"
  if(contactAV.getEtatBouton()==true){
    Serial.println("le contact AVANT est appuyé");
  }
  else{
    Serial.println("rien");
  }
  delay(1000);
}
