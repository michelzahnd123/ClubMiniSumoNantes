#include <Arduino.h>
#include "bouton.h"
Bouton contact(18);

void setup() {
  Serial.begin(115200);
  contact.setPinBouton(18);
}

void loop() {
  if(contact.getEtatBouton()==true){
    Serial.println("le bouton est appuyé");
  }
  else{
    Serial.println("rien");
  }
  delay(1000);
}
