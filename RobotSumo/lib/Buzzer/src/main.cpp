#include <Arduino.h>
#include "buzzer.h"

#define pin_beep 13

Buzzer beep(pin_beep);
int tempsAllume=50;
int tempsEteint=949;

void setup() {
  Serial.begin(115200);
  beep.setPinBuzzer(pin_beep);
}

void loop() {
  Serial.println(" Beep !!! ");
  beep.on();
  delay(tempsAllume);
  beep.off();
	delay(tempsEteint);
}