#include <Arduino.h>
#include "led.h"

//bouton pin 15
//led rouge pin 2
//led verte pin 4
//led blanche pin 16
//led bleue pin 17
Led ledRouge(2);
Led ledVerte(4);
Led ledBlanche(16);
Led ledBleue(17);

#define TEMPS 500

void setup() {
  Serial.begin(115200);
}


void loop() {
  //faire un chenillard
  ledRouge.on();
  delay(TEMPS);
  ledRouge.off();
  ledVerte.on();
  delay(TEMPS);
  ledVerte.off();
  ledBlanche.on();
  delay(TEMPS);
  ledBlanche.off();
  ledBleue.on();
  delay(TEMPS);
  ledBleue.off();
}
