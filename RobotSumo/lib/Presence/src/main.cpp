#include <Arduino.h>
#include "presence.h"
#define pin_JS40F_G 2
#define pin_JS40F_D 23

Presence JS40F_G(pin_JS40F_G);
Presence JS40F_D(pin_JS40F_D);

void setup() {
  Serial.begin(115200);
  JS40F_G.setPinPresence(pin_JS40F_G);
  JS40F_D.setPinPresence(pin_JS40F_D);
}

void loop() {
if(JS40F_G.getEtatPresence()){
	Serial.println("Qq chose à l'Avant Gauche");
	}
if(JS40F_D.getEtatPresence()){
	Serial.println("Qq chose à l'Avant Droite");
	}
delay(500);

}